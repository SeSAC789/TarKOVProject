// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/HealthComp.h"
#include "KJH/HPWidget.h"
#include "Blueprint/UserWidget.h"
#include <Subsystems/PanelExtensionSubsystem.h>

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	 // 각 신체 부위별 기본 HP 값 초기화
	BodyPartMaxHP.Add( "Head" , 35.0f );
	BodyPartMaxHP.Add( "Thorax" , 85.0f );
	BodyPartMaxHP.Add( "Stomach" , 70.0f );
	BodyPartMaxHP.Add( "RightArm" , 60.0f );
	BodyPartMaxHP.Add( "LeftArm" , 60.0f );
	BodyPartMaxHP.Add( "RightLeg" , 65.0f );
	BodyPartMaxHP.Add( "LeftLeg" , 65.0f );

	// MaxHP 값을 사용하여 각 부위의 현재 건강 상태 초기화
	for (const auto& Elem : BodyPartMaxHP)
	{
		BodyPartHP.Add( Elem.Key , Elem.Value );
	}
}


// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	statusComp = Cast<UStatusEffectComp>( GetOwner()->GetComponentByClass( UStatusEffectComp::StaticClass() ) );


	
}


// Called every frame
void UHealthComp::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );

	

	// ...
}

void UHealthComp::TakeDamage( const FName& BodyPart , float DamageAmount, const FString& HitObjectName )
{
	
	if (BodyPartHP.Contains( BodyPart ))
	{
		bool isBleedingDamage = HitObjectName.Equals( TEXT( "Bleeding Effect" ) , ESearchCase::IgnoreCase );

		// 체력 감소 로직
		if (!isBleedingDamage || BodyPartHP[BodyPart] > 0.0f)
		{
			BodyPartHP[BodyPart] = FMath::Clamp<float>( BodyPartHP[BodyPart] - DamageAmount , 0.0f , BodyPartMaxHP[BodyPart] );
			UE_LOG( LogTemp , Warning , TEXT( "%s 부위가 %f 만큼 데미지를 받았습니다 %s로 인해서 현재 남은 HP: %f" ) , *BodyPart.ToString() , DamageAmount , *HitObjectName , BodyPartHP[BodyPart] );
		}

		// 머리나 흉부가 출혈로 0이 됐을 경우를 제외하고, 출혈이 아닌 다른 원인으로 0이 되면 즉시 사망 처리
		if ((BodyPart == FName( "Head" ) || BodyPart == FName( "Thorax" )) && BodyPartHP[BodyPart] <= 0.0f && !isBleedingDamage)
		{
			bIsDead = true;
			UE_LOG( LogTemp , Warning , TEXT( "Character has died due to critical damage to %s from %s." ) , *BodyPart.ToString() , *HitObjectName );
			// 즉시 사망 이후 관련 함수 구현
			return;
		}

		if (BodyPartHP[BodyPart] <= 0.0f)
		{
			// 체력이 0인 부위에 추가적인 피해 발생 시 분산 로직 호출
			DistributeDamage( DamageAmount , BodyPart );
		}

		// 모든 신체 부위 체력이 0 이하 확인
		CheckAndHandleTotalDepletion();
	
	}
	CheckAndApplyBleeding( BodyPart );
	CheckAndApplyFracture( BodyPart );
}

void UHealthComp::CheckAndHandleTotalDepletion()
{
	bIsDead = true; // 일단 사망한 것으로 가정
	for (const auto& Elem : BodyPartHP)
	{
		if (Elem.Value > 0)
		{
			bIsDead = false; // 하나라도 체력이 0보다 큰 부위가 있다면 캐릭터는 아직 살아있음
			break;
		}
	}

	if (bIsDead)
	{
		UE_LOG( LogTemp , Warning , TEXT( "Character has died due to total HP depletion." ) );
		// 모든 신체 부위의 체력이 0 이하이면 사망 처리 구현 하면 될 듯
	}
}

void UHealthComp::HealBodyPart(FName BodyPart, float HealAmount)
{
	// 체력을 회복시킵니다.
	if (BodyPartHP.Contains( BodyPart ))
	{
		BodyPartHP[BodyPart] = FMath::Clamp<float>( BodyPartHP[BodyPart] + HealAmount , 0.0f , BodyPartMaxHP[BodyPart] );
		UE_LOG( LogTemp , Warning , TEXT( "%s 부위가 %f 만큼 회복되었습니다. 현재 HP: %f" ) , *BodyPart.ToString() , HealAmount , BodyPartHP[BodyPart] );
	}

	// 체력이 특정 수준 이상 회복되었으면 출혈 상태이상 비활성화
	if (GetBodyPartHealth( BodyPart ) > GetBodyPartMaxHealth( BodyPart ) * 0.5f)
	{
		if (statusComp)
		{
			// 출혈 상태이상 해제
			statusComp->ClearStatusEffect( EStatusEffectType::Bleeding, BodyPart );
		}
	}

	// 골절은 추후에 힐 아이템 구현 시 부목을 통해서만 해제가능 하게

	//// 체력이 30% 초과로 회복되었으면 골절 상태이상 비활성화
	//if (GetBodyPartHealth( BodyPart ) > GetBodyPartMaxHealth( BodyPart ) * 0.3f)
	//{
	//	if (statusComp)
	//	{
	//		// 골절 상태이상 해제
	//		statusComp->ClearStatusEffect( EStatusEffectType::Fracture );
	//		UE_LOG( LogTemp , Warning , TEXT( "%s 부위의 골절 상태이상이 해제되었습니다." ) , *BodyPart.ToString() );
	//	}
	//}
}

float UHealthComp::GetBodyPartHealth( FName BodyPart )
{
	// 체력을 저장하는 TMap에서 BodyPart에 해당하는 값을 찾아 반환
	if (BodyPartHP.Contains( BodyPart ))
	{
		return BodyPartHP[BodyPart];
	}
	else
	{
		// 만약 해당 부위의 체력 정보가 없는 경우, 0을 반환
		return 0.0f;
	}
}

float UHealthComp::GetBodyPartMaxHealth(FName BodyPart )
{
	if (BodyPartMaxHP.Contains( BodyPart ))
	{
		return BodyPartMaxHP[BodyPart];
	}
	else
	{
		return 0.0f; // 부위에 해당하는 최대 체력 정보가 없으면 0 반환
	}
}

void UHealthComp::CheckAndApplyBleeding(const FName& BodyPart)
{
	if (BodyPartHP[BodyPart] <= (BodyPartMaxHP[BodyPart] * 0.5f))
	{
		// StatusEffectComp에 출혈 상태이상 적용 요청
		if (statusComp)
		{
			statusComp->ApplyStatusEffect( EStatusEffectType::Bleeding, BodyPart );
			UE_LOG( LogTemp , Warning , TEXT( "UHealthComp::CheckAndApplyBleeding" ) );
			UE_LOG( LogTemp , Warning , TEXT( "출혈상태 생긴 부위 :  %s" ) , *BodyPart.ToString() );
		}
	}
}

void UHealthComp::CheckAndApplyFracture(const FName& BodyPart)
{
	 // 골절이 다리 부위에만 적용되도록 조건 추가
    if ((BodyPart == FName("LeftLeg") || BodyPart == FName("RightLeg")) && BodyPartHP[BodyPart] <= (BodyPartMaxHP[BodyPart] * 0.3f))
    {
        if (statusComp)
        {
            statusComp->ApplyStatusEffect(EStatusEffectType::Fracture, BodyPart);
            UE_LOG(LogTemp, Warning, TEXT("UHealthComp::CheckAndApplyFracture, 골절 상태 생긴 부위: %s"), *BodyPart.ToString());
        }
    }
}

void UHealthComp::DistributeDamage(float DamageAmount, FName IgnoredBodyPart)
{
	float DamageMultiplier = 1.0f; // 기본 피해량 배수

	// 피해 분산 배수 조정
	if (IgnoredBodyPart == "RightArm" || IgnoredBodyPart == "LeftArm")
	{
		DamageMultiplier = 0.7f;
	}
	else if (IgnoredBodyPart == "Stomach")
	{
		DamageMultiplier = 1.5f;
	}
	
	// 조정된 분산 피해량 계산
	float DistributedDamage = (DamageAmount * DamageMultiplier) / (BodyPartHP.Num() - 1);

	// 다른 모든 신체 부위로 피해 분산
	for (auto& Elem : BodyPartHP)
	{
		if (Elem.Key != IgnoredBodyPart)
		{
			float NewHP = FMath::Clamp( Elem.Value - DistributedDamage , 0.0f , BodyPartMaxHP[Elem.Key] );
			UE_LOG( LogTemp , Warning , TEXT( "%s 부위에 %f 만큼의 피해가 분산되었습니다. 변경 전 HP: %f, 변경 후 HP: %f" ) , *Elem.Key.ToString() , DistributedDamage , Elem.Value , NewHP );
			Elem.Value = NewHP;
		}
	}
}

