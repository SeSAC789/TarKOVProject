// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// *------------------------메인UI------------------------* //
	UPROPERTY(EditDefaultsOnly)
	class UEditableText* edit_username;

	UPROPERTY( EditDefaultsOnly )
	class UButton* btn_lobby;

	UFUNCTION()
	void OnClickGoLobby();

	
};
