// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/Trigger/TriggerBase1.h"
#include "TriggerEscapeLocation.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API ATriggerEscapeLocation : public ATriggerBase1
{
	GENERATED_BODY()

private:
	ATriggerEscapeLocation();

	UFUNCTION()
	virtual void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY()
	class UGameOverWidget* GameOverUI;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> GameOverUIFactory;

	UPROPERTY()
	class UGameClearWidget* GameClearUI;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> GameClearUIFactory;
	
};
