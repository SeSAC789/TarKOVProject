// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API APlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void CheckGameOverCondition();

	void CheckGameClearCondition();


};
