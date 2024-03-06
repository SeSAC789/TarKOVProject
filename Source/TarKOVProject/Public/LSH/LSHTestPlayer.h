// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBase.h"
#include "LSHTestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API ALSHTestPlayer : public APlayerBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditDefaultsOnly )
	class UPlayerMoveComp* moveComp1;

	ALSHTestPlayer();

	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;


	///////////////////


	virtual void BeginPlay() override;

};
