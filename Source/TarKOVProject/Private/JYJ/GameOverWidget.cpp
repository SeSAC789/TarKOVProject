// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/GameOverWidget.h"

#include "Components/Button.h"
#include "JYJ/Controller/TarKOVPlayerController.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_restart->OnClicked.AddDynamic( this , &UGameOverWidget::OnClickbtnRestart );
	btn_quit->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickbtnQuit );
}

void UGameOverWidget::OnClickbtnQuit()
{
	auto pc = Cast<ATarKOVPlayerController>( GetWorld()->GetFirstPlayerController() );
	pc->Pause();
}

void UGameOverWidget::OnClickbtnRestart()
{
	//플레이어 컨트롤러를 가져오고 싶다.
	auto pc = Cast<ATarKOVPlayerController>( GetWorld()->GetFirstPlayerController() );

	if (pc)
	{
		//마우스 커서를 안보이게 하고 싶다.
		pc->SetShowMouseCursor( false );
		//SetShowGameOverUI( false );

		//server retry를 호출하고 싶다.
		pc->ServerRetry();

		
	}
}
