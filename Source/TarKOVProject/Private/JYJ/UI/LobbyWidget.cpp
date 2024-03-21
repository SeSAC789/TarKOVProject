// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/UI/LobbyWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "JYJ/GameInstance/TarKOVGameInstance.h"
#include "Components/WidgetSwitcher.h"

const int SWITCH_INDEX_MENU = 0;
const int SWITCH_INDEX_FINDROOM = 1;
const int SWITCH_INDEX_CREATEROOM = 2;


void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor( true );

	gi = GetWorld()->GetGameInstance<UTarKOVGameInstance>();

	// 버튼 Bind
	btn_lobby->OnClicked.AddDynamic(this, &ULobbyWidget::OnClickGoLobby );
	btn_createroom->OnClicked.AddDynamic(this, &ULobbyWidget::OnCreateRoom);
	
}

void ULobbyWidget::SwitchPanel(int32 index)
{
	switcher_lobby->SetActiveWidgetIndex( index );
}

void ULobbyWidget::OnClickGoLobby()
{
	SwitchPanel(SWITCH_INDEX_FINDROOM);
	UE_LOG( LogTemp , Warning , TEXT( "ULobbyWidget::OnClickGoLobby - test1" ) );
}

void ULobbyWidget::OnCreateRoom()
{
	if(gi)
	{
		if(false == edit_username->GetText().IsEmpty())
		{
			gi->myNickName = edit_username->GetText().ToString();
		} else
		{
			edit_username->SetText(FText::FromString(gi->myNickName));
		}
		//SwitchPanel(SWITCH_INDEX_CREATEROOM);

	}

	UE_LOG(LogTemp, Warning, TEXT("ULobbyWidget::OnCreateRoom - test1"));
	gi->CreateRoom(TEXT("TEST"));
}
