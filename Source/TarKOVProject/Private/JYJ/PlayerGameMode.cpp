// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerGameMode.h"

#include "JYJ/Controller/TarKOVPlayerController.h"
#include "JYJ/GameOverWidget.h"
#include "KJH/HPWidget.h"

void APlayerGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerGameMode::CheckGameOverCondition()
{
    // 모든 PlayerControllers 순회
    for (FConstPlayerControllerIterator i = GetWorld()->GetPlayerControllerIterator(); i; ++i)
    {
        ATarKOVPlayerController* pc = Cast<ATarKOVPlayerController>( *i );
        if (pc)
        {
            // 플레이어의 킬 카운트 가져오기
            int32 KillCount = pc->GetKillCount();

            // 게임 오버 UI에 킬 카운트 업데이트
            UGameOverWidget* GameOverUI = Cast<UGameOverWidget>( pc->GetGameOverUI() );
            if (GameOverUI)
            {
                GameOverUI->UpdatePlayerKillCount( KillCount );
            }
        }
    }
}

void APlayerGameMode::CheckGameClearCondition()
{
    // 모든 PlayerControllers 순회
    for (FConstPlayerControllerIterator i = GetWorld()->GetPlayerControllerIterator(); i; ++i)
    {
        ATarKOVPlayerController* pc = Cast<ATarKOVPlayerController>( *i );
        if (pc)
        {
            // 플레이어의 킬 카운트 가져오기
            int32 KillCount = pc->GetKillCount();

            // 게임 클리어 UI에 킬 카운트 업데이트
            UGameClearWidget* GameClearUI = Cast<UGameClearWidget>( pc->GetGameClearUI() );
            if (GameClearUI)
            {
                GameClearUI->UpdatePlayerKillCount( KillCount );
            }
        }
    }
}