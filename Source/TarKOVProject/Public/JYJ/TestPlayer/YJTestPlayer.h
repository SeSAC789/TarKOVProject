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
	AYJTestPlayer();
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;

public:
	// client to server. 손에 붙여 주세요. (총 액터의 포인터)
	UFUNCTION( Server , Reliable )
	void ServerRPCSpawnPistol( AActor* pistol );				//요청
};
