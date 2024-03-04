// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBase.h"
#include "YJTestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API AYJTestPlayer : public APlayerBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditDefaultsOnly )
	class UPlayerMoveComp* moveComp1;

	AYJTestPlayer();

	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
};
