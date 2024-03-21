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
		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject( this , &UTarKOVGameInstance::OnFindOtherRoomsComplete );
		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject( this , &UTarKOVGameInstance::OnJoinRoomComplete );
		
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
	UE_LOG( LogTemp , Warning , TEXT( "UTarKOVGameInstance::FindOtherRooms" ) );
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
	// 검색할 때 onFindingRoomsDelegate => false
	// 성공 실패와 무관하게
	if (onFindingRoomsDelegate.IsBound())
	{
		onFindingRoomsDelegate.Broadcast( false );

	}

	UE_LOG( LogTemp , Warning , TEXT( "OnMyFindOtherRoomsComplete - Sucess" ) );

	//for(auto r : roomSearch->SearchResults)
	for (int32 i = 0; i < roomSearch->SearchResults.Num(); i++)
	{
		UE_LOG( LogTemp , Warning , TEXT( "OnMyFindOtherRoomsComplete - Loop" ) );
		auto r = roomSearch->SearchResults[i];

		if (false == r.IsValid())
			continue;		//그 다음으로 넘김

		FRoomInfo info;

		info.index = i;

		//넘겨 받은 session settings = SessionSettings (위에 선언한거)
		r.Session.SessionSettings.Get( TEXT( "ROOM_NAME" ) , info.roomName );

		r.Session.SessionSettings.Get( TEXT( "HOST_NAME" ) , info.hostName );

		//FString userName;
		//userName = r.Session.OwningUserName;

		//공개방 , Session Settings 에 있는 것은 방장이 설정한 값
		int32 max = r.Session.SessionSettings.NumPublicConnections;
		//현재 방이 몇명 들어와 있는지 (들어올 수 있는 명 수 - 현재 오픈된 connection 갯수(입장 가능 수))
		int32 current = max - r.Session.NumOpenPublicConnections;

		info.playerCount = FString::Printf( TEXT( "%d / %d" ) , current , max );

		//ping 정보
		info.pingMS = FString::Printf( TEXT( "%d ms" ) , r.PingInMs );

		info.printLog();

		// 만약 바인된 함수가 있다면 info를 넘겨줌
		if (onAddRoomInfoDelegate.IsBound())
		{
			onAddRoomInfoDelegate.Broadcast( info );
		}

	}
}

void UTarKOVGameInstance::JoinRoom(int32 index)
{
	auto r = roomSearch->SearchResults[index];

	//Session name = Room Name
	FString sessionName;
	r.Session.SessionSettings.Get( TEXT( "ROOM_NAME" ) , sessionName );

	sessionInterface->JoinSession( 0 , FName( *sessionName ) , r );
}

void UTarKOVGameInstance::OnJoinRoomComplete(FName sessionName, EOnJoinSessionCompleteResult::Type result)
{
	//성공했다면?
	if (EOnJoinSessionCompleteResult::Success == result)
	{
		//입장한 방의 이름을 기억하고 싶다.
		myRoomName = sessionName.ToString();

		//서버의 주소를 받아와서
		//접속하는 문자열?? 서버에 접속하는 문자열,.,. 서버의 주소로 간주
		FString url;
		sessionInterface->GetResolvedConnectString( sessionName , url );
		//여행을 떠나고 싶다.
		auto pc = GetWorld()->GetFirstPlayerController();

		//TRAVEL_Absolute 값을 아무것도 안 가지고 서버로 떠남!
		pc->ClientTravel( url , TRAVEL_Absolute );

	}
	//그렇지 않다면
	else
	{
		UE_LOG( LogTemp , Warning , TEXT( "Join Session Failed... : %d" ) , result );
	}
}


