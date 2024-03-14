// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	class UTextBlock* text_deathreason;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* text_timer;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (BindWidget) )
	class UButton* btn_quit;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , meta = (BindWidget) )
	class UButton* btn_restart;

private:
	void OnClickbtnQuit();
	void OnClickbtnRestart();

};
