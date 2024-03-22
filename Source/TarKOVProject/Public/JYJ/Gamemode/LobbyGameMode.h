// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 *
 */
UCLASS()
class TARKOVPROJECT_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	ALobbyGameMode();
	virtual void BeginPlay() override;

public:
	//WBP_HttpUI를 생성해서 화면에 보이게 하고 싶다. / meta -> 블루프린트에서 노출
	UPROPERTY( EditDefaultsOnly , meta = (AllowPrivateAccess) )
	TSubclassOf<class ULobbyWidget> lobbyFactory;

	class ULobbyWidget* lobbyUI;

};
