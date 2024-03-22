// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/UI/RoomInfoWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "JYJ/GameInstance/TarKOVGameInstance.h"

void URoomInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_enter->OnClicked.AddDynamic(this, &URoomInfoWidget::OnClickEnter);
}

void URoomInfoWidget::OnClickEnter()
{
	auto gi = Cast<UTarKOVGameInstance>( GetWorld()->GetGameInstance() );
	gi->JoinRoom( roomIndex );
}

void URoomInfoWidget::SetInfo(const FRoomInfo& info)
{

	UE_LOG(LogTemp, Warning, TEXT("URoomInfoWidget::SetInfo"));
	roomIndex = info.index;

	txt_roomname->SetText(FText::FromString(*info.roomName));
	txt_username->SetText(FText::FromString(*info.hostName));
	txt_playernum->SetText(FText::FromString(*info.playerCount));
	txt_pingms->SetText(FText::FromString(*info.pingMS));


}


