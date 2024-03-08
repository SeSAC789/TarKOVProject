// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/HealthComp.h"

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
		// 체력이 이미 0이라면 데미지를 적용하지 않는다
		if (BodyPartHP[BodyPart] <= 0.0f)
		{
			UE_LOG( LogTemp , Warning , TEXT( "%s part is already at 0 HP due to %s. No further damage applied." ) , *BodyPart.ToString() , *HitObjectName );
			return; // 더 이상 코드를 실행하지 않고 빠져나갑니다.
		}

		BodyPartHP[BodyPart] = FMath::Clamp<float>( BodyPartHP[BodyPart] - DamageAmount , 0.0f , BodyPartMaxHP[BodyPart] );
		UE_LOG( LogTemp , Warning , TEXT( "%s received %f damage from %s. Remaining HP: %f" ) , *BodyPart.ToString() , DamageAmount , *HitObjectName , BodyPartHP[BodyPart] );

		// 만약 머리 또는 흉부 부위의 체력이 0 이하라면 즉시 사망
		if ((BodyPart == FName( "Head" ) || BodyPart == FName( "Thorax" )) && BodyPartHP[BodyPart] <= 0)
		{
			bIsDead = true;
			UE_LOG( LogTemp , Warning , TEXT( "Character has died due to critical damage to %s from %s." ) , *BodyPart.ToString() , *HitObjectName );
			// 즉시 사망 이후 관련 함수 구현하자, 죽음 애니메이션 제생, 게임오버 ui등 구현하면 될 듯
			return;
		}

		// 모든 신체 부위의 체력이 0 이하인지 확인
		bIsDead = true; // 처음에는 캐릭터를 사망한 것으로 가정
		for (const auto& Elem : BodyPartHP)
		{
			if (Elem.Value > 0)
			{
				bIsDead = false; // 하나라도 체력이 0보다 큰 부위가 있다면, 캐릭터는 아직 살아있음
				break;
			}
		}

		// 만약 모든 신체 부위의 체력이 0 이하이면 사망 처리
		if (bIsDead)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Character has died due to total HP depletion." ) );
			// 즉시 사망 이후 관련 함수 구현하자, 죽음 애니메이션 제생, 게임오버 ui등 구현하면 될 듯

		}
	}
	CheckAndApplyBleeding( BodyPart );
	CheckAndApplyFracture( BodyPart );
}

void UHealthComp::HealBodyPart(FName BodyPart, float HealAmount)
{
	// 체력 회복이건 추후에 블프에서 구현 할 듯?

	// 체력이 특정 수준 이상 회복되었으면 출혈 상태이상 비활성화
	if (GetBodyPartHealth( BodyPart ) > GetBodyPartMaxHealth( BodyPart ) * 0.5f)
	{
		
		if (statusComp)
		{
			statusComp->ClearStatusEffect( EStatusEffectType::Bleeding );
		}
	}
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
	if (BodyPartHP[BodyPart] <= (BodyPartMaxHP[BodyPart] * 0.3f))
	{
		// StatusEffectComp에 골절 상태이상 적용 요청
		if (statusComp)
		{
			statusComp->ApplyStatusEffect( EStatusEffectType::Fracture, BodyPart );
			UE_LOG( LogTemp , Warning , TEXT( "UHealthComp::CheckAndApplyFracture" ) );
			UE_LOG( LogTemp , Warning , TEXT( "골절상태 생긴 부위 :  %s" ) , *BodyPart.ToString() );

		}
	}
}

