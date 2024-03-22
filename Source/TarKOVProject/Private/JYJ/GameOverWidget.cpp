// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/GameOverWidget.h"
#include "Components/Button.h"
#include "JYJ/Controller/TarKOVPlayerController.h"
#include "JYJ/GameInstance/TarKOVGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_restart->OnClicked.AddDynamic( this , &UGameOverWidget::OnClickbtnRestart );
	btn_quit->OnClicked.AddDynamic(this, &UGameOverWidget::OnClickbtnQuit );
}

void UGameOverWidget::OnClickbtnQuit()
{
	auto pc = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame( GetWorld() , pc , EQuitPreference::Quit , false );

}

void UGameOverWidget::OnClickbtnRestart()
{
	auto gi = GetGameInstance<UTarKOVGameInstance>();
	gi->ExitRoom();
	btn_quit->SetIsEnabled( false );
}
