// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/UI/RoomInfoWidget.h"

#include "Components/Button.h"

void URoomInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_enter->OnClicked.AddDynamic(this, &URoomInfoWidget::OnClickEnter);
}

void URoomInfoWidget::OnClickEnter()
{
	
}

void URoomInfoWidget::SetInfo(const FRoomInfo& info)
{
	
}


