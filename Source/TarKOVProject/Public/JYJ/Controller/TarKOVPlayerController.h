// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JYJ/UI/GameClearWidget.h"
#include "TarKOVPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API ATarKOVPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATarKOVPlayerController();

	UPROPERTY()
	class APlayerGameMode* gm;

	virtual void BeginPlay() override;

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite )
	int32 killCnt = 0;

	// Kill Count
	void UpdatekillCnt(int32 killOtherPlayer);

	UFUNCTION()
	int32 GetKillCount() const;


	// Player MainUI
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UHPWidget> PlayerMainUIFactory;

	UPROPERTY()
	class UHPWidget* PlayerMainUI;

	// Game Over UI -> Player HP == 0 일 때, 해당 UI 실행.
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UGameOverWidget> GameOverUIFactory;

	UPROPERTY( Transient )
	class UGameOverWidget* GameOverUI;

	// Game Clear UI -> Trigger에서 5초 지나면 실행
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UGameClearWidget> GameClearUIFactory;

	UFUNCTION( BlueprintCallable )
	UGameOverWidget* GetGameOverUI() const;

	UFUNCTION( BlueprintCallable )
	UGameClearWidget* GetGameClearUI() const;

	UPROPERTY( Transient )
	class UGameClearWidget* GameClearUI;

	UFUNCTION( Server , Reliable )
	void ServerRetry();

	// gameover 게임 시작 시간을 기록
	UPROPERTY( ReplicatedUsing = OnRep_GameStartTime )
	int32 GameStartTime;

	// 플레이 시간을 저장
	UPROPERTY( Replicated, EditAnywhere )
	int32 PlayTime;

	UFUNCTION()
	void OnRep_GameStartTime();

	void CalculatePlayTime();

	// 클리어시 ui에 timer보이게
	UFUNCTION( BlueprintCallable )
	void ShowEscapeUI( bool bShow );

	// gameclear 플레이 타임을 저장
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Replicated )
	int32 PlayerPlayTime;

	// 게임 클리어 시 호출
	void CalculateAndSavePlayTime();

	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
};
