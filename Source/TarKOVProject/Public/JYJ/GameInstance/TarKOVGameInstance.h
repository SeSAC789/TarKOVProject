// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Interfaces/OnlineSessionInterface.h>
#include "Engine/GameInstance.h"
#include "TarKOVGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UTarKOVGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	IOnlineSessionPtr sessionInterface;

	void Createroom();
	
};
