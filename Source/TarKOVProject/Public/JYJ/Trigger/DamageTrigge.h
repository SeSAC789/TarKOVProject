// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/Trigger/TriggerBase1.h"
#include "DamageTrigge.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API ADamageTrigge : public ATriggerBase1
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnHitboxOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );
	
};
