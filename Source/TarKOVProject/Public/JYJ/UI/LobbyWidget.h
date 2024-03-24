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

	UPROPERTY()
	class UTarKOVGameInstance* gi;

	// *------------------------메인UI------------------------* //
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UWidgetSwitcher* switcher_lobby;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableText* edit_username;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UEditableText* edit_roomname;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UButton* btn_lobby;

	UPROPERTY( EditDefaultsOnly, meta=(BindWidget))
	class UScrollBox* scroll_roomlists;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class URoomInfoWidget> roomInfoFactory;


	void SwitchPanel( int32 index );

	UFUNCTION()
	void OnClickGoLobby();

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UButton* btn_createroom;

	UFUNCTION()
	void OnCreateRoom();

	UFUNCTION()
	void OnFindRoomList();

	UFUNCTION()
	void AddRoomInfoWidget( const struct FRoomInfo& info );

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* clickSFX;
	
};
