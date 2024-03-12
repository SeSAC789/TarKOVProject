// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TARKOVPROJECT_API UStaminaComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // 다리 스태미나
    UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stamina" )
    float LegStaminaMax=100.0f;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stamina" )
    float LegStamina=LegStaminaMax;


    // 팔 스태미나
    UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stamina" )
    float ArmStaminaMax=100.0f;

    UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stamina" )
    float ArmStamina=ArmStaminaMax;

    
    // 스태미나 감소 및 회복 변수
    UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stamina" )
    float StaminaDrainRate = 1.0f;

    UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stamina" )
    float StaminaRecoveryRate = 5.0f;;

    UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Stamina" )
    float StaminaJumpCost= 10.0f;

    // 스태미나 관련 함수들
    void UpdateLegStamina( float DeltaTime );
    void UpdateArmStamina( float DeltaTime );

    // 스태미나 소모 함수
    void ConsumeStaminaForJump();
    void ConsumeStaminaForRun( float DeltaTime );

    // 스태미나 회복 함수
    void RecoverStamina( float DeltaTime );

    // 스태미나 점검 함수
    bool CanPerformLegAction();
    bool CanPerformArmAction();
};
