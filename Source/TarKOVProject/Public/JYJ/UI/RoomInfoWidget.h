// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API URoomInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* txt_roomname;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UTextBlock* txt_username;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UTextBlock* txt_playernum;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UTextBlock* txt_pingms;

	UPROPERTY( EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_enter;

	UFUNCTION()
	void OnClickEnter();

	void SetInfo(const struct FRoomInfo& info);
};
