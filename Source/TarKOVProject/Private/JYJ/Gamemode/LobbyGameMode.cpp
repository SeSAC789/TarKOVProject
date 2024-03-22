// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Gamemode/LobbyGameMode.h"
#include "Blueprint/UserWidget.h"
#include "JYJ/UI/LobbyWidget.h"

ALobbyGameMode::ALobbyGameMode()
{
	ConstructorHelpers::FClassFinder<ULobbyWidget> tmpUI( TEXT( "/Script/UMGEditor.WidgetBlueprint'/Game/TarKOV/JYJ/Blueprints/UI/WBP_LobbyWidget.WBP_LobbyWidget_C'" ) );
	if (tmpUI.Succeeded())
	{
		lobbyFactory = tmpUI.Class;
	}
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
}
