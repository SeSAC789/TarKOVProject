// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HPWidget.h"
#include "JYJ/PlayerBase.h"
#include "JHPlayerTest.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API AJHPlayerTest : public APlayerBase
{
	GENERATED_BODY()

	AJHPlayerTest();

public:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void OnHitboxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Components" )
	class UStatusEffectComp* statusComp;

	UPROPERTY( BlueprintReadOnly )
	class UHPWidget* hpUI;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> hpUIFactory;

};
