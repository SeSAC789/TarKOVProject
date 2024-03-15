// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/StaminaComp.h"

// Sets default values for this component's properties
UStaminaComp::UStaminaComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStaminaComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStaminaComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RecoverStamina( DeltaTime );
}

void UStaminaComp::ConsumeStamina(float Amount)
{
	Stamina = FMath::Clamp( Stamina - Amount , 0.0f , MaxStamina );
}

void UStaminaComp::RecoverStamina(float DeltaTime)
{
	if (Stamina < MaxStamina)
	{
		Stamina = FMath::Clamp( Stamina + StaminaRecoveryRate * DeltaTime , 0.0f , MaxStamina );
	}
}


