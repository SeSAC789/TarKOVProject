// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerGameMode.h"

#include "JYJ/Controller/TarKOVPlayerController.h"
#include "JYJ/GameOverWidget.h"

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
            UGameOverWidget* GameOverWidget = Cast<UGameOverWidget>( pc->GetGameOverUI() );
            if (GameOverWidget)
            {
                GameOverWidget->UpdatePlayerKillCount( KillCount );
            }
        }
    }
}
