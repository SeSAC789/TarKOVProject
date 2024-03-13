// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/StatusEffectComp.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/PlayerComp/PlayerMoveComp.h"
#include "KJH/HealthComp.h"
#include "Net/UnrealNetwork.h"
#include "TarKOVProject/TarKOVProject.h"


// Sets default values for this component's properties
UStatusEffectComp::UStatusEffectComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SetIsReplicatedByDefault( true );
}


// Called when the game starts
void UStatusEffectComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	me = Cast<APlayerBase>( GetOwner() );
	healthComp = Cast<UHealthComp>( me->GetComponentByClass( UHealthComp::StaticClass() ) );
	moveComp = Cast<UPlayerMoveComp>( me->GetComponentByClass( UPlayerMoveComp::StaticClass() ) );
}


// Called every frame
void UStatusEffectComp::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );

	// ...

	UpdateStatusEffects( DeltaTime );
}

void UStatusEffectComp::ApplyStatusEffect( EStatusEffectType NewEffectType , FName BodyPart )
{
	// 상태이상 데이터가 이미 존재하는지 확인
	FStatusEffectData* ExistingEffect = StatusEffects.FindByPredicate( [&]( const FStatusEffectData& Data ) {
		return Data.EffectType == NewEffectType;
	} );

	// 상태이상이 존재하지 않는 경우, 새로 추가
	if (ExistingEffect == nullptr)
	{
		FStatusEffectData NewEffectData = { NewEffectType, true, BodyPart };
		StatusEffects.Add( NewEffectData );

		UE_LOG( LogTemp , Warning , TEXT( " UStatusEffectComp::ApplyStatusEffect, 상태효과 적용 : %s 부위 : %s " ) , *GETENUMSTRING( "EStatusEffectType" , NewEffectType ) , *BodyPart.ToString() );
	}
}

void UStatusEffectComp::ClearStatusEffect( EStatusEffectType EffectType , FName BodyPart )
{
	for (auto& Effect : StatusEffects)
	{
		if (Effect.EffectType == EffectType && Effect.BodyPart == BodyPart)
		{
			Effect.bIsActive = false;
			break; // 일치하는 첫 상태이상만 비활성화 후 반복 종료
		}
	}
}

void UStatusEffectComp::UpdateStatusEffects( float DeltaTime )
{
	for (auto& EffectData : StatusEffects)
	{
		if (!EffectData.bIsActive) continue;

		EffectData.Timer += DeltaTime;

		// 출혈이나 골절 상태이상이 활성화된 경우, 고통 타이머를 업데이트합니다.
		if (EffectData.EffectType == EStatusEffectType::Bleeding || EffectData.EffectType == EStatusEffectType::Fracture)
		{
			EffectData.PainTimer += DeltaTime;
			// 고통 상태이상을 적용합니다.
			if (EffectData.PainTimer >= 20.0f && !IsPain())
			{
				ApplyPainEffect( EffectData , DeltaTime );
			}
		}

		switch (EffectData.EffectType)
		{
		case EStatusEffectType::Bleeding:   ApplyBleedingEffect( EffectData , DeltaTime );            break;
		case EStatusEffectType::Fracture:   ApplyFractureEffect( EffectData , DeltaTime );            break;
		case EStatusEffectType::Pain:       ApplyPainEffect( EffectData , DeltaTime );                break;
		default: break;
		}
	}
}

void UStatusEffectComp::ApplyBleedingEffect( FStatusEffectData& EffectData , float DeltaTime )
{
	if (!healthComp) return;
	UE_LOG( LogTemp , Warning , TEXT( " UStatusEffectComp::ApplyBleedingEffect" ) );
	// 출혈 상태이상의 타이머 업데이트
	EffectData.Timer += DeltaTime;

	// 5초마다 출혈 데미지 적용
	if (EffectData.Timer >= 5.0f)
	{
		// 타이머 리셋
		EffectData.Timer = 0.0f;

		// 부위 별 체력이 50%이하라면 이 조건은 healthcomp에서 
		if (healthComp)
		{
			// 해당 부위에 데미지 3씩 적용
			healthComp->TakeDamage( EffectData.BodyPart , 3.0f , TEXT( "Bleeding Effect" ) );

			UE_LOG( LogTemp , Warning , TEXT( "UStatusEffectComp::ApplyBleedingEffect, 출혈상태 : %s 부위 %d damage." ) , *EffectData.BodyPart.ToString() , 3 );
		}
	}
}

void UStatusEffectComp::ApplyFractureEffect( FStatusEffectData& EffectData , float DeltaTime )
{
	if (!healthComp) return;

	EffectData.Timer += DeltaTime;

	if (me && healthComp)
	{
		if (EffectData.BodyPart == "RightLeg" || EffectData.BodyPart == "LeftLeg")
		{
			if (!EffectData.bIsSpeedModified) // 속도 조정이 아직 적용되지 않았다면
			{
				float speedModifier = 0.55f;
				me->GetCharacterMovement()->MaxWalkSpeed *= speedModifier;
				me->GetCharacterMovement()->JumpZVelocity *= speedModifier;
				UE_LOG( LogTemp , Warning , TEXT( "UStatusEffectComp::ApplyFractureEffect, 속도 및 점프 높이 감소 적용" ) );
				EffectData.bIsSpeedModified = true; // 속도 조정 적용 완료
			}

			if (moveComp && moveComp->IsRunning())
			{
				EffectData.RunningTimer += DeltaTime;
				if (EffectData.RunningTimer >= 1.0f) // 1초마다
				{
					EffectData.RunningTimer = 0.0f; // 타이머 리셋
					healthComp->TakeDamage( EffectData.BodyPart , 1.0f , "Fracture" );
					UE_LOG( LogTemp , Warning , TEXT( "UStatusEffectComp::ApplyFractureEffect, 골절상태 달리기 시 추가 데미지" ) );
				}
			}
			else
			{
				EffectData.RunningTimer = 0.0f; // 달리기를 멈추면 타이머 리셋
			}
		}
	}
}

void UStatusEffectComp::ApplyPainEffect( FStatusEffectData& EffectData , float DeltaTime )
{

}

bool UStatusEffectComp::IsBleeding() const
{
	for (const FStatusEffectData& Effect : StatusEffects)
	{
		if (Effect.bIsActive && Effect.EffectType == EStatusEffectType::Bleeding)
		{
			return true;
		}
	}
	return false;
}

bool UStatusEffectComp::IsFractured() const
{
	for (const FStatusEffectData& Effect : StatusEffects)
	{
		if (Effect.bIsActive && Effect.EffectType == EStatusEffectType::Fracture)
		{
			return true;
		}
	}
	return false;
}

bool UStatusEffectComp::IsPain() const
{
	for (const FStatusEffectData& Effect : StatusEffects)
	{
		if (Effect.bIsActive && Effect.EffectType == EStatusEffectType::Pain)
		{
			return true;
		}
	}
	return false;
}

void UStatusEffectComp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( UStatusEffectComp , StatusEffects );
	
}
