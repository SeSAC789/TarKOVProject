// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Interfaces/OnlineSessionInterface.h>
#include "Engine/GameInstance.h"
#include "TarKOVGameInstance.generated.h"

USTRUCT( BlueprintType )
struct FRoomInfo
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly )
	int32 index;
	UPROPERTY( EditDefaultsOnly )
	FString roomName;
	UPROPERTY( EditDefaultsOnly )
	FString hostName;
	UPROPERTY( EditDefaultsOnly )
	FString playerCount;
	UPROPERTY( EditDefaultsOnly )
	FString pingMS;

	FORCEINLINE void printLog() const	//const -> 값 변경 불가
	{
		UE_LOG( LogTemp , Warning , TEXT( "Roomname : %s, Hostaname : %s, playerCnt : %s, pintInfo : %s" ) , *roomName , *hostName , *playerCount , *pingMS );
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFindingRoomsDelegate , bool , bActive );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FAddRoomInfoDelegate , const FRoomInfo& , roomInfo );

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UTarKOVGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	IOnlineSessionPtr sessionInterface;

	FString myNickName;

	FString myRoomName;

	// 방 생성
	void CreateRoom(FString roomName);
	void OnCreateRoomComplete(FName sessionName, bool bWasSuccessful);


	// 방 찾기
	TSharedPtr<FOnlineSessionSearch> roomSearch;

	//방검색의 타이밍에 대한 Delegate
	FFindingRoomsDelegate onFindingRoomsDelegate;

	//방검색 후 방생성에 관련된 Delegate
	FAddRoomInfoDelegate onAddRoomInfoDelegate;

	void FindOtherRooms();
	void OnFindOtherRoomsComplete( bool bWasSuccessful );

	//방 입장 요청
	void JoinRoom( int32 index );

	//방 입장 응답
	void OnJoinRoomComplete( FName sessionName , EOnJoinSessionCompleteResult::Type result );

	//방 퇴장 요청
	void ExitRoom();

	//방 퇴장 응답
	UFUNCTION()
	void OnExitRoomComplete( FName sessionName , bool bWasSuccessful );

	UFUNCTION( Server , Reliable )
	void ServerExitRoom();

	UFUNCTION( NetMulticast , Reliable )
	void MultiExitRoom();

	FString StringBase64Encode( const FString& str );
	FString StringBase64Decode( const FString& str );
	
};
