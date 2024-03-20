// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/UI/LobbyWidget.h"

#include "Components/Button.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_lobby->OnClicked.AddDynamic(this, &ULobbyWidget::OnClickGoLobby );
	
}

void ULobbyWidget::OnClickGoLobby()
{

}
