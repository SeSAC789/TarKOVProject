// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Controller/TarKOVPlayerController.h"
#include "GameFramework/Character.h"
#include "JYJ/PlayerGameMode.h"

ATarKOVPlayerController::ATarKOVPlayerController()
{

}

void ATarKOVPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 태어날 때, 내가 서버라면 게임모드를 기억하고 싶다.
	if (HasAuthority())
	{
		gm = Cast<APlayerGameMode>( GetWorld()->GetAuthGameMode() );
	}
}

void ATarKOVPlayerController::ServerRetry_Implementation()
{
	//이곳은 서버에서 호출되는 함수이다.
	// 재시작 요청이 오면
	// 현재 캐릭터를 기억하고
	auto character = this->GetCharacter();
	// 현재 플레이어를 UnPossess 하고
	UnPossess();
	// 기억한 캐릭터를 파괴하고,
	character->Destroy(); 
	// 게임 모드에게 재시작하라고 한다.
	//check( gm )
	if (nullptr == gm)
	{
		gm = Cast<APlayerGameMode>( GetWorld()->GetAuthGameMode() );
	}

	if (gm)
	{
		gm->RestartPlayer( this );
	}
}
