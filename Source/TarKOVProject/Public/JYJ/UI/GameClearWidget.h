// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UGameClearWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* text_clear;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* text_timer;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (BindWidget) )
	class UButton* btn_quit;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (BindWidget) )
	class UButton* btn_restart;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* text_KillCount;
	

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (BindWidgetAnim), Transient )
	class UWidgetAnimation* GameClearAnimation;

	UFUNCTION( BlueprintCallable )
	void SetPlayTime( int32 PlayTime );

	UFUNCTION( BlueprintCallable )
	void UpdatePlayerKillCount( int32 KillCount );

	FText GetKillCountText() const;

private:
	UFUNCTION()
	void OnClickbtnQuit();
	UFUNCTION()
	void OnClickbtnRestart();
};
