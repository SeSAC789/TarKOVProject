// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/GameInstance/TarKOVGameInstance.h"
#include "OnlineSubsystem.h"

void UTarKOVGameInstance::Init()
{
	Super::Init();

	if(auto subsystem = IOnlineSubsystem::Get())
	{
		sessionInterface = subsystem->GetSessionInterface();

		//Delegate관련 코드
		//sessionInterface->OnCreateSessionCompleteDelegates.AddUObject( this , &UTarKOVGameInstance::OnMyCreateRoomComplete );
		//sessionInterface->OnFindSessionsCompleteDelegates.AddUObject( this , &UTarKOVGameInstance::OnMyFindOtherRoomsComplete );
		
	}
}

void UTarKOVGameInstance::Createroom()
{
}
