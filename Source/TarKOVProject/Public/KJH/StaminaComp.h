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



	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Stamina" )
	float MaxStamina = 100.0f;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Stamina", Replicated )
	float Stamina = MaxStamina;

	// 스태미나 회복률
	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Stamina" )
	float StaminaRecoveryRate = 3.0f;

	// 스태미나 소모률
	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Stamina" )
	float StaminaConsumptionRate = 3.0f;

	void ConsumeStamina( float Amount );

	void RecoverStamina( float DeltaTime );

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
};
