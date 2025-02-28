﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KJH/JHPlayerTest.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();
	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

	UPROPERTY()
	class APlayerBase* player;
	
	////테스트 위해 jhplayer 추가
	///UPROPERTY()
	class AJHPlayerTest* JHplayer;

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
	bool bValidPistol;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bAimRifle;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float pitch;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float yaw;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float roll;

	UPROPERTY( EditDefaultsOnly )
	class UAnimMontage* fireMontage;

	UPROPERTY( EditDefaultsOnly )
	class UAnimMontage* reloadMontage;

	UPROPERTY( EditDefaultsOnly )
	class UAnimMontage* grenadeMontage;

	UPROPERTY()
	class UGameOverWidget* GameOverUI;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> GameOverUIFactory;

	UPROPERTY( EditDefaultsOnly )
	class USoundBase* footstepSFX;


	void playFireRifleAnimation();
	void playFirePistolAnimation();

	void playReloadRifleAnimation();
	void playReloadPistolAnimation();

	void playGrenadeAnimation();

	UFUNCTION()
	void AnimNotify_OnGameOver();

	UFUNCTION()
	void AnimNotify_OnThrowGrenade();

	UFUNCTION()
	void AnimNotify_OnWalking();
	
};
