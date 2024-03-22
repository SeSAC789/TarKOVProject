// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/UI/GameClearWidget.h"
#include "Components/Button.h"
#include "JYJ/Controller/TarKOVPlayerController.h"
#include "JYJ/GameInstance/TarKOVGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameClearWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(GameClearAnimation, 0, 0);

	btn_restart->OnClicked.AddDynamic( this , &UGameClearWidget::OnClickbtnRestart ); 
	btn_quit->OnClicked.AddDynamic( this , &UGameClearWidget::OnClickbtnQuit );
}

void UGameClearWidget::OnClickbtnQuit()
{
	auto pc = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame( GetWorld() , pc , EQuitPreference::Quit , false );
}

void UGameClearWidget::OnClickbtnRestart()
{
	auto gi = GetGameInstance<UTarKOVGameInstance>();
	gi->ExitRoom();
	btn_quit->SetIsEnabled( false );
}
