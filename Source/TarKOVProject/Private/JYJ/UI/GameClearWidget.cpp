// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/UI/GameClearWidget.h"
#include "Components/Button.h"
#include "JYJ/Controller/TarKOVPlayerController.h"
#include "JYJ/GameInstance/TarKOVGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UGameClearWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(GameClearAnimation, 0, 0);

	ATarKOVPlayerController* pc = Cast<ATarKOVPlayerController>( GetOwningPlayer() );
	if (pc)
	{
		// 킬 카운트 
		UpdatePlayerKillCount( pc->GetKillCount() );
	}

	btn_restart->OnClicked.AddDynamic( this , &UGameClearWidget::OnClickbtnRestart ); 
	btn_quit->OnClicked.AddDynamic( this , &UGameClearWidget::OnClickbtnQuit );
}

void UGameClearWidget::SetPlayTime(float PlayTime)
{
	text_timer->SetText( FText::FromString( FString::Printf( TEXT( "레이드 시간: %0.2f " ) , PlayTime ) ) );
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

void UGameClearWidget::UpdatePlayerKillCount( int32 KillCount )
{
	if (text_KillCount)
	{
		text_KillCount->SetText( FText::AsNumber( KillCount ) );
	}
}

FText UGameClearWidget::GetKillCountText() const
{
	const ATarKOVPlayerController* pc = Cast<ATarKOVPlayerController>( GetOwningPlayer() );
	if (pc)
	{
		int32 KillCount = pc->GetKillCount();
		return FText::AsNumber( KillCount );
	}

	return FText::GetEmpty();
}