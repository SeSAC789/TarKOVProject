// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/GameInstance/TarKOVGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

void UTarKOVGameInstance::Init()
{
	Super::Init();

	if(auto subsystem = IOnlineSubsystem::Get())
	{
		sessionInterface = subsystem->GetSessionInterface();

		//Delegate관련 코드
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject( this , &UTarKOVGameInstance::OnCreateRoomComplete );
		//sessionInterface->OnFindSessionsCompleteDelegates.AddUObject( this , &UTarKOVGameInstance::OnMyFindOtherRoomsComplete );
		
	}
}

void UTarKOVGameInstance::CreateRoom(FString roomName)
{
	//UE_LOG(LogTemp, Warning, TEXT("Create Room [%s]!!!!!!!!!!!!1"), *roomName);

	FOnlineSessionSettings setting;

	//데디케이트 서버인가
	setting.bIsDedicated = false;
	//랜선인가
	auto subSys = IOnlineSubsystem::Get();
	setting.bIsLANMatch = subSys->GetSubsystemName().IsEqual( "NULL" );

	//공개로 입장할 수 있는가, 아니면 친구 초대로만?
	setting.bShouldAdvertise = true;

	//온라인 상태를 공개적으로 사용할 것인가? -> ping 정보
	setting.bUsesPresence = true;

	//중간입장이 가능한가? -> 모든 사람이 입장 가능
	setting.bAllowJoinInProgress = true;
	setting.bAllowJoinViaPresence = true;

	//최대 입장 가능한 수 설정
	setting.NumPublicConnections = 5;

	//커스텀 정보 설정
	setting.Set( TEXT( "HOST_NAME" ) , myNickName , EOnlineDataAdvertisementType::ViaOnlineServiceAndPing );
	setting.Set( TEXT( "ROOM_NAME" ) , roomName ,	EOnlineDataAdvertisementType::ViaOnlineServiceAndPing );

	//netID 설정
	FUniqueNetIdPtr _netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().GetUniqueNetId();

	UE_LOG( LogTemp , Warning , TEXT( ">>Create Room Start! Room Name = [%s], netID = [%s]" ) , *roomName , *_netID->ToString() );
	sessionInterface->CreateSession( *_netID , FName( *roomName ) , setting );
}

void UTarKOVGameInstance::OnCreateRoomComplete(FName sessionName, bool bWasSuccessful)
{
	UE_LOG( LogTemp , Warning , TEXT( ">>OnMyCreateRoomComplete! Session Name = [%s], bWasSuccessful = [%d]" ) , *sessionName.ToString() , bWasSuccessful );

	//방을 생성했다면
	if (bWasSuccessful)
	{
		// 입장한 방의 이름을 기억하고 싶다.
		myRoomName = sessionName.ToString();

		//서버는 세계 여행을 떠나고 싶다. 어디로?
		FString url = TEXT( "/Game/TarKOV/Maps/BetaMap?listen" );
		GetWorld()->ServerTravel( url );

		//서버면서 client 인 상태

	}
}

void UTarKOVGameInstance::FindOtherRooms()
{
	//1. FOnlineSessionSearch객체를 생성
	roomSearch = MakeShareable( new FOnlineSessionSearch );

	//2. 세션 검색 조건 설정
	roomSearch->QuerySettings.Set( SEARCH_PRESENCE , true , EOnlineComparisonOp::Equals );

	//3. 최대 검색 갯수를 정하고 싶다.
	roomSearch->MaxSearchResults = 10;

	//4. 랜선인지 아닌지를 정하고 싶다.
	auto subSys = IOnlineSubsystem::Get();
	roomSearch->bIsLanQuery = subSys->GetSubsystemName().IsEqual( "NULL" );


	//5. 검색을 하고 싶다. = sessionInterface를 사용해서 검색
	//스마트 포인터를 레퍼런스로 바꾸는 함수가 있음 ex) roomSearch.ToSharedRef()
	sessionInterface->FindSessions( 0 , roomSearch.ToSharedRef() );

	//검색할 때 onFindingRoomsDelegate => true
	if (onFindingRoomsDelegate.IsBound())
	{
		onFindingRoomsDelegate.Broadcast( true );

	}
}

void UTarKOVGameInstance::OnFindOtherRoomsComplete(bool bWasSuccessful)
{
	
}


