// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/UI/LobbyWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "JYJ/GameInstance/TarKOVGameInstance.h"
#include "Components/WidgetSwitcher.h"
#include "JYJ/UI/RoomInfoWidget.h"

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

	OnFindRoomList();
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

	FString _roomname = edit_roomname->GetText().ToString();

	UE_LOG(LogTemp, Warning, TEXT("ULobbyWidget::OnCreateRoom - test1"));
	gi->CreateRoom( _roomname );
}

void ULobbyWidget::OnFindRoomList()
{
	UE_LOG(LogTemp, Warning, TEXT("ULobbyWidget::OnFindRoomList - TEST1"));
	//게임 인스턴스가 있다면
	if (gi)
	{
		UE_LOG( LogTemp , Warning , TEXT( "ULobbyWidget::OnFindRoomList - TEST2" ) );
		//이름을 적었다면
		if (false == edit_username->GetText().IsEmpty())
		{
			//적은 이름을 내 닉네임으로 하고 싶다.
			gi->myNickName = edit_username->GetText().ToString();
		}
		else
		{
			//기본 이름을 적고 싶다.
			edit_username->SetText( FText::FromString( gi->myNickName ) );
		}

		gi->FindOtherRooms();
		gi->onAddRoomInfoDelegate.AddDynamic( this , &ULobbyWidget::AddRoomInfoWidget );



	}
}

void ULobbyWidget::AddRoomInfoWidget(const FRoomInfo& info)
{
	if (nullptr == roomInfoFactory || nullptr == scroll_roomlists) return;

	UE_LOG(LogTemp, Warning, TEXT("ULobbyWidget::AddRoomInfoWidget"));
	//위젯을 생성해서 roominfofactory
	auto roomInfo = CreateWidget<URoomInfoWidget>( GetWorld() , roomInfoFactory );

	// 넘겨받은 info 값으로 UI 셋팅
	roomInfo->SetInfo( info );
	//roomInfoWidget = CreateWidget<URoomInfoWidget>(TEXT("roomInfoWidget"));

	//scolllist에 자식으로 붙이고 싶다.
	scroll_roomlists->AddChild( Cast<UWidget>( roomInfo ) );
}
