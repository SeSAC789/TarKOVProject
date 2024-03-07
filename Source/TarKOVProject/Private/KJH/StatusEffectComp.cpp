// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/StatusEffectComp.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/PlayerComp/PlayerMoveComp.h"
#include "KJH/HealthComp.h"
#include "TarKOVProject/TarKOVProject.h"


// Sets default values for this component's properties
UStatusEffectComp::UStatusEffectComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


// Called when the game starts
void UStatusEffectComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
    me = Cast<APlayerBase>( GetOwner() );
    healthComp = Cast<UHealthComp>( GetOwner()->GetComponentByClass( UHealthComp::StaticClass() ) );
}


// Called every frame
void UStatusEffectComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

    UpdateStatusEffects(DeltaTime);
}

void UStatusEffectComp::ApplyStatusEffect(EStatusEffectType NewEffectType)
{
    // 상태이상 데이터가 이미 존재하는지 확인
    FStatusEffectData* ExistingEffect = StatusEffects.FindByPredicate( [&]( const FStatusEffectData& Data ) {
        return Data.EffectType == NewEffectType;
    } );

    // 상태이상이 존재하지 않는 경우, 새로 추가
    if (ExistingEffect == nullptr)
    {
        FStatusEffectData NewEffectData = { NewEffectType, true };
        StatusEffects.Add( NewEffectData );

        UE_LOG( LogTemp , Warning , TEXT( " UStatusEffectComp::ApplyStatusEffect, Status Effect Applied: %s" ) , *GETENUMSTRING( "EStatusEffectType" , NewEffectType ) );
    }
}

void UStatusEffectComp::ClearStatusEffect(EStatusEffectType EffectType)
{
    for (auto& Effect : StatusEffects)
    {
        if (Effect.EffectType == EffectType)
        {
            Effect.bIsActive = false;
            break; // 일치하는 첫 상태이상만 비활성화 후 반복 종료
        }
    }
}

void UStatusEffectComp::UpdateStatusEffects(float DeltaTime)
{
    for (auto& EffectData : StatusEffects)
    {
        if (!EffectData.bIsActive) continue;

        switch (EffectData.EffectType)
        {
        case EStatusEffectType::Bleeding:   ApplyBleedingEffect( EffectData , DeltaTime );            break;
        case EStatusEffectType::Fracture:   ApplyFractureEffect( EffectData , DeltaTime );            break;
        case EStatusEffectType::Pain:       ApplyPainEffect( EffectData , DeltaTime );                break;
        default: break;
        }
    }
}

void UStatusEffectComp::ApplyBleedingEffect(FStatusEffectData& EffectData, float DeltaTime)
{
    // 출혈 상태이상의 타이머 업데이트
    EffectData.Timer += DeltaTime;

    // 5초마다 출혈 데미지 적용
    if (EffectData.Timer >= 5.0f)
    {
        // 타이머 리셋
        EffectData.Timer = 0.0f;

        // 부위 별 체력이 50%이하라면
        if (healthComp && healthComp->GetBodyPartHealth( EffectData.BodyPart ) <= healthComp->GetBodyPartMaxHealth( EffectData.BodyPart ) * 0.5f)
        {
            // 해당 부위에 데미지 3씩 적용
            healthComp->TakeDamage( EffectData.BodyPart , 3.0f , TEXT( "Bleeding Effect" ) );
        }
    }
}

void UStatusEffectComp::ApplyFractureEffect( FStatusEffectData& EffectData, float DeltaTime)
{
    // 골절 상태이상의 타이머 업데이트
    EffectData.Timer += DeltaTime;

    if (me)
    {
        if (EffectData.FracturedBodyPart == "RightLeg" || EffectData.FracturedBodyPart == "LeftLeg")
        {
            me->GetCharacterMovement()->MaxWalkSpeed *= 0.55f;
            me->GetCharacterMovement()->JumpZVelocity *= 0.55f;

            // 달리기 하면 데미지
            UPlayerMoveComp* moveComp = Cast<UPlayerMoveComp>( me->GetComponentByClass( UPlayerMoveComp::StaticClass() ) );

            if (moveComp && moveComp->IsRunning())
            {
                // 달리기 상태이면 추가 데미지 타이머 시작
                if (moveComp->IsRunning())
                {
                    EffectData.RunningTimer += DeltaTime;

                    // 5초마다 데미지 적용
                    if (EffectData.RunningTimer >= 5.0f)
                    {
                        EffectData.RunningTimer = 0.0f; // 타이머 리셋
                        healthComp->TakeDamage( EffectData.FracturedBodyPart , 3.0f , "Fracture" );
                    }
                }
                else
                {
                    EffectData.RunningTimer = 0.0f; // 달리기를 멈추면 타이머 리셋
                }
            }
        }
    }
}

void UStatusEffectComp::ApplyPainEffect(FStatusEffectData& EffectData, float DeltaTime)
{

}

