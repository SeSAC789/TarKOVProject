﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBaseComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TARKOVPROJECT_API UPlayerBaseComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerBaseComp();

protected:
	// Called when the game starts
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	FORCEINLINE virtual void SetupInput(class UEnhancedInputComponent* input)
	{
	}

	UPROPERTY()
	class APlayerBase* me;
};
