// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/GameOverWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "JYJ/Controller/TarKOVPlayerController.h"
#include "JYJ/GameInstance/TarKOVGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ATarKOVPlayerController* pc = Cast<ATarKOVPlayerController>( GetOwningPlayer() );
	if (pc)
	{
		int32 Minutes = pc->PlayTime / 60;
		int32 Seconds = pc->PlayTime % 60;
		FString PlayTimeText = FString::Printf( TEXT( "레이드 시간 :  %02d:%02d" ) , Minutes , Seconds );
		text_timer->SetText( FText::FromString( PlayTimeText ) );
		/*FString PlayTimeText = FString::Printf( TEXT( "레이드 시간 : %.2f " ) , pc->PlayTime );
		text_timer->SetText( FText::FromString( PlayTimeText ) );*/

		// 킬 카운트 
		UpdatePlayerKillCount( pc->GetKillCount() );
	}

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

void UGameOverWidget::UpdatePlayerKillCount( int32 KillCount )
{
	if (text_KillCount)
	{
		text_KillCount->SetText( FText::AsNumber( KillCount ) );
	}
}

FText UGameOverWidget::GetKillCountText() const
{
	const ATarKOVPlayerController* pc = Cast<ATarKOVPlayerController>( GetOwningPlayer() );
	if (pc)
	{
		int32 KillCount = pc->GetKillCount();
		return FText::AsNumber( KillCount );
	}

	return FText::GetEmpty();
}