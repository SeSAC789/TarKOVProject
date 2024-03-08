// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float speed;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float direction;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool isInAir;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool isCrouched;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool isProned;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool isDie;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bValidRifle;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bAimRifle;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float pitch;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float yaw;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float roll;

	UPROPERTY( EditDefaultsOnly )
	class UAnimMontage* fireRifleMontage;

	void playFireAnimation();
	
};
