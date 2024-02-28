// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayBase.generated.h"

UCLASS()
class TARKOVPROJECT_API APlayBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* camComp;

	UPROPERTY(EditAnywhere)
	FVector direction;

	UPROPERTY(EditAnywhere)
	float runMultiply;

	UFUNCTION()
	void OnAxisVertical(float value);

	UFUNCTION()
	void OnAxisHorixontal(float value);

	UFUNCTION()
	void OnAxisTurnYaw(float value);

	UFUNCTION()
	void OnAxisTurnPitch(float value);

	void OnActionJump();
	void Sprint();
	void StopSprinting();


};
