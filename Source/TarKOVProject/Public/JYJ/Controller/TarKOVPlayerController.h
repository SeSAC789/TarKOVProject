// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TarKOVPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API ATarKOVPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATarKOVPlayerController();

	UPROPERTY()
	class APlayerGameMode* gm;

	virtual void BeginPlay() override;

	// Player MainUI
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UHPWidget> PlayerMainUIFactory;

	UPROPERTY()
	class UHPWidget* PlayerMainUI;

	// Game Over UI -> Player HP == 0 일 때, 해당 UI 실행.
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UGameOverWidget> GameOverUIFactory;

	UPROPERTY()
	class UGameOverWidget* GameOverUI;

	UFUNCTION( Server , Reliable )
	void ServerRetry();
	
};
