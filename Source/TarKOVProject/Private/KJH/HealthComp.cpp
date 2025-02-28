﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/HealthComp.h"
#include "KJH/HPWidget.h"
#include "Blueprint/UserWidget.h"
#include <Subsystems/PanelExtensionSubsystem.h>

#include "Components/Image.h"
#include "JYJ/GameOverWidget.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/Controller/TarKOVPlayerController.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


	 // 각 신체 부위별 기본 HP 값 TArray로 초기화
	BodyPartHP.Add( FBodyPartHealthData( "Head" , 35.0f , 35.0f ) );
	BodyPartHP.Add( FBodyPartHealthData( "Thorax" , 85.0f , 85.0f ) );
	BodyPartHP.Add( FBodyPartHealthData( "Stomach" , 70.0f , 70.0f ) );
	BodyPartHP.Add( FBodyPartHealthData( "RightArm" , 60.0f , 60.0f ) );
	BodyPartHP.Add( FBodyPartHealthData( "LeftArm" , 60.0f , 60.0f ) );
	BodyPartHP.Add( FBodyPartHealthData( "RightLeg" , 65.0f , 65.0f ) );
	BodyPartHP.Add( FBodyPartHealthData( "LeftLeg" , 65.0f , 65.0f ) );

	SetIsReplicatedByDefault( true );
}


// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	statusComp = Cast<UStatusEffectComp>( GetOwner()->GetComponentByClass( UStatusEffectComp::StaticClass() ) );
	me = Cast<APlayerBase>( GetOwner() );

}


// Called every frame
void UHealthComp::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );


	// ...
}

void UHealthComp::TakeDamage( const FName& BodyPart , float DamageAmount , const FString& HitObjectName )
{
	if (bIsDead)
	{
		return;
	}

	if (!me && !me->PlayerMainUI)
	{
		return;
	}

	if (me->PlayerMainUI)
	{
		UE_LOG( LogTemp , Warning , TEXT( "UHealthComp::TakeDamage play anim" ) )
			me->PlayerMainUI->Hit_Img->SetVisibility( ESlateVisibility::Visible );
		me->PlayerMainUI->PlayHitAnim();

	}

	bool bFoundBodyPart = false;

	// TArray를 순회하면서 해당 신체 부위를 찾는다
	for (FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.BodyPart == BodyPart)
		{
			// 신체 부위를 찾았으므로, 해당 부위의 체력을 감소시킵니다.
			bool isBleedingDamage = HitObjectName.Equals( TEXT( "Bleeding Effect" ) , ESearchCase::IgnoreCase );
			if (!isBleedingDamage || BodyPartData.HP > 0.0f)
			{

				float NewHP = GetBodyPartHealth( BodyPart ) - DamageAmount;
				SetBodyPartHP( BodyPart , NewHP );

				CheckAndApplyBleeding( BodyPart );
				//BodyPartData.HP = FMath::Clamp<float>( BodyPartData.HP - DamageAmount , 0.0f , BodyPartData.MaxHP );

				UE_LOG( LogTemp , Warning , TEXT( "%s 부위가 %f 만큼 데미지를 받았습니다 %s로 인해서 현재 남은 HP: %f" ) , *BodyPart.ToString() , DamageAmount , *HitObjectName , BodyPartData.HP );
			}

			// 머리나 흉부가 0이 됐을 경우 캐릭터를 사망 처리합니다. // 출혈로 인한 데미지가 아닐 경우
			if ((BodyPart == FName( "Head" ) || BodyPart == FName( "Thorax" )) && BodyPartData.HP <= 0.0f && !isBleedingDamage)
			{
				bIsDead = true;
				ATarKOVPlayerController* pc = Cast<ATarKOVPlayerController>( me->GetController() );
				if (pc && me)
				{
					pc->CalculatePlayTime();
					pc->DisableInput( pc ); // 죽으면 인풋 안받게
					me->OnDeath(); // 죽으면 충돌체 비활성화
				}

				//me->invenDie();
				UE_LOG( LogTemp , Warning , TEXT( "%s 부위가 %s 로 인해 데미지 받아 즉시 사망." ) , *BodyPart.ToString() , *HitObjectName );
				return;
			}

			if (BodyPartData.HP <= 0.0f)
			{
				// 체력이 0인 부위에 추가적인 피해 발생 시 분산 로직을 호출.
				DistributeDamage( DamageAmount , BodyPart );
			}

			bFoundBodyPart = true;
			break;
		}
	}

	if (bFoundBodyPart)
	{
		// 모든 신체 부위 체력이 0 이하인지 확인합니다.
		CheckAndHandleTotalDepletion();
		// 해당 부위에 출혈 및 골절 상태를 적용.
		//CheckAndApplyBleeding( BodyPart );
		CheckAndApplyFracture( BodyPart );

	}
	else
	{
		// BodyPart 이름을 찾을 수 없습니다. 오류 로깅이나 예외 처리가 필요할 수 있습니다.
		UE_LOG( LogTemp , Error , TEXT( "Attempted to take damage on an undefined body part: %s" ) , *BodyPart.ToString() );
	}
}

void UHealthComp::TakeDamage( float DamageAmount , const FString& HitObjectName )
{
	for (FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		float NewHP = GetBodyPartHealth( BodyPartData.BodyPart ) - DamageAmount;
		SetBodyPartHP( BodyPartData.BodyPart , NewHP );
	}
}

void UHealthComp::CheckAndHandleTotalDepletion()
{
	bIsDead = true; // 일단 사망한 것으로 가정

	// TArray를 순회하면서 각 신체 부위의 체력 확인
	for (const FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.HP > 0)
		{
			bIsDead = false; // 하나라도 체력이 0보다 큰 부위가 있다면 캐릭터는 아직 살아있음
			break; // 하나라도 생존해 있다면 더 이상 확인할 필요 없으므로 반복문 탈출
		}
	}

	if (bIsDead)
	{
		ATarKOVPlayerController* pc = Cast<ATarKOVPlayerController>( me->GetController() );
		if (pc && me)
		{
			pc->CalculatePlayTime();
			pc->DisableInput( pc );
			me->OnDeath();
		}
		UE_LOG( LogTemp , Warning , TEXT( "모든 부위 hp가 다 0이 되어 죽음." ) );
		//me->invenDie();
	}
}

void UHealthComp::HealBodyPart( FName BodyPart , float HealAmount )
{
	// 체력을 회복시킵니다.
	for (FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.BodyPart == BodyPart)
		{
			float NewHP = GetBodyPartHealth( BodyPart ) + HealAmount;
			SetBodyPartHP( BodyPart , NewHP );

			//BodyPartData.HP = FMath::Clamp<float>( BodyPartData.HP + HealAmount , 0.0f , BodyPartData.MaxHP );
			UE_LOG( LogTemp , Warning , TEXT( "%s 부위가 %f 만큼 회복되었습니다. 현재 HP: %f" ) , *BodyPart.ToString() , HealAmount , BodyPartData.HP );

			break; // 해당 부위를 찾았으니 루프를 종료합니다.
		}
	}
}

bool UHealthComp::IsInjured( FName BodyPart ) const
{
	for (const FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.BodyPart == BodyPart)
		{
			// 해당 부위의 체력이 최대 체력보다 낮은 경우 다친 것으로 판단
			return BodyPartData.HP < BodyPartData.MaxHP;
		}
	}
	return false; // 해당 부위를 찾지 못하면 다치지 않은 것으로 간주
}

float UHealthComp::GetBodyPartHealth( FName BodyPart )
{
	for (const FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.BodyPart == BodyPart)
		{
			return BodyPartData.HP;
		}
	}

	// 만약 해당 부위의 체력 정보가 없는 경우, 0을 반환
	return 0.0f;
}

float UHealthComp::GetBodyPartMaxHealth( FName BodyPart )
{
	for (const FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.BodyPart == BodyPart)
		{
			return BodyPartData.MaxHP;
		}
	}

	// 만약 해당 부위의 최대 체력 정보가 없는 경우, 0을 반환
	return 0.0f;
}

void UHealthComp::SetBodyPartHP( FName BodyPart , float NewHP )
{
	for (FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.BodyPart == BodyPart)
		{
			BodyPartData.HP = FMath::Clamp( NewHP , 0.0f , BodyPartData.MaxHP );

			if (BodyPartData.HP <= 0)
			{
				// 추가 사망 처리 로직
			}
			break;
		}
	}

	OnRep_BodyPartHP();
}

void UHealthComp::OnRep_BodyPartHP()
{

}

void UHealthComp::CheckAndApplyBleeding( const FName& BodyPart )
{
	for (const FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.BodyPart == BodyPart && BodyPartData.HP <= (BodyPartData.MaxHP * 0.5f))
		{
			// StatusEffectComp에 출혈 상태이상 적용
			if (statusComp)
			{
				statusComp->ApplyStatusEffect( EStatusEffectType::Bleeding , BodyPart );
				UE_LOG( LogTemp , Warning , TEXT( "UHealthComp::CheckAndApplyBleeding, 출혈상태 생긴 부위 :  %s" ) , *BodyPart.ToString() );
			}
			break;
		}
	}
}

void UHealthComp::CheckAndApplyFracture( const FName& BodyPart )
{
	// 골절이 다리 부위에만 적용되도록 조건 추가
	for (const FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if ((BodyPart == FName( "LeftLeg" ) || BodyPart == FName( "RightLeg" )) &&
			BodyPartData.BodyPart == BodyPart &&
			BodyPartData.HP <= (BodyPartData.MaxHP * 0.3f))
		{
			if (statusComp)
			{
				statusComp->ApplyStatusEffect( EStatusEffectType::Fracture , BodyPart );
				UE_LOG( LogTemp , Warning , TEXT( "UHealthComp::CheckAndApplyFracture, 골절 상태 생긴 부위: %s" ) , *BodyPart.ToString() );
			}
			break; // 해당하는 부위에 대한 처리를 완료했으므로 루프를 종료합니다.
		}
	}
}

// 머리랑 흉부 제외하고 각 부위 파괴 시 받은 데미지 다른 부위로 분산

void UHealthComp::DistributeDamage( float DamageAmount , FName IgnoredBodyPart )
{
	if (bIsDead)
	{
		return;
	}

	float DamageMultiplier = 1.0f; // 기본 피해량 배수

	// 부위 별 피해 분산 배수 조정 
	if (IgnoredBodyPart == "RightArm" || IgnoredBodyPart == "LeftArm")
	{
		DamageMultiplier = 0.7f;
	}
	else if (IgnoredBodyPart == "Stomach")
	{
		DamageMultiplier = 1.5f;
	}

	// 실제 분산될 신체 부위의 수 계산 (IgnoredBodyPart 제외)
	int DistributablePartsCount = BodyPartHP.Num(); // 모든 신체 부위를 기본 값으로 설정

	// IgnoredBodyPart가 지정되어 있다면, 분산될 신체 부위의 수에서 1을 빼서 계산
	if (!IgnoredBodyPart.IsNone())
	{
		DistributablePartsCount -= 1;
	}

	// 조정된 분산 피해량 계산
	float DistributedDamage = (DamageAmount * DamageMultiplier) / FMath::Max( 1 , DistributablePartsCount );

	// 다른 모든 신체 부위로 피해 분산
	for (FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.BodyPart != IgnoredBodyPart)
		{
			float NewHP = FMath::Clamp( BodyPartData.HP - DistributedDamage , 0.0f , BodyPartData.MaxHP );
			UE_LOG( LogTemp , Warning , TEXT( "%s 부위에 %f 만큼의 피해가 분산되었습니다. 변경 전 HP: %f, 변경 후 HP: %f" ) , *BodyPartData.BodyPart.ToString() , DistributedDamage , BodyPartData.HP , NewHP );
			BodyPartData.HP = NewHP;
		}
	}
}

FName UHealthComp::FindWeakestBodyPart()
{
	FName WeakestPart = NAME_None;
	float MinHP = 100;

	for (const FBodyPartHealthData& Part : BodyPartHP)
	{
		if (Part.HP < MinHP)
		{
			MinHP = Part.HP;
			WeakestPart = Part.BodyPart;
		}
	}
	return WeakestPart;
}

FName UHealthComp::FindWeakestFracturedBodyPart() const
{
	FName WeakestPart = NAME_None;
	float MinHP = 100;

	for (const FBodyPartHealthData& Part : BodyPartHP)
	{
		// 부위가 골절되었는지 확인
		if (statusComp->IsFractured( Part.BodyPart ) && Part.HP < MinHP)
		{
			MinHP = Part.HP;
			WeakestPart = Part.BodyPart;
		}
	}
	return WeakestPart;
}


TArray<FName> UHealthComp::GetBleedingBodyParts() const
{
	TArray<FName> BleedingParts;
	if (statusComp)
	{
		for (const FBodyPartHealthData& BodyPartData : BodyPartHP)
		{
			if (statusComp->IsBleeding( BodyPartData.BodyPart ))
			{
				BleedingParts.Add( BodyPartData.BodyPart );
			}
		}
	}
	return BleedingParts;
}

TArray<FName> UHealthComp::GetFracturedBodyParts() const
{
	TArray<FName> FracturedParts;
	if (statusComp)
	{
		for (const FBodyPartHealthData& BodyPartData : BodyPartHP)
		{
			if (statusComp->IsFractured( BodyPartData.BodyPart ))
			{
				FracturedParts.Add( BodyPartData.BodyPart );
			}
		}
	}
	return FracturedParts;
}

TArray<FName> UHealthComp::GetInjuredBodyParts() const
{
	TArray<FName> InjuredParts;
	for (const FBodyPartHealthData& BodyPartData : BodyPartHP)
	{
		if (BodyPartData.HP < BodyPartData.MaxHP)
		{
			InjuredParts.Add( BodyPartData.BodyPart );
		}
	}
	return InjuredParts;
}

bool UHealthComp::IsDead()
{
	return bIsDead;
}

void UHealthComp::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UHealthComp , BodyPartHP );
	DOREPLIFETIME( UHealthComp , bIsDead );
}

