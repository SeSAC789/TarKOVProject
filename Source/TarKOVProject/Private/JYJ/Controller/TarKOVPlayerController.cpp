// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Controller/TarKOVPlayerController.h"
#include "GameFramework/Character.h"
#include "JYJ/PlayerGameMode.h"
#include "Net/UnrealNetwork.h"

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

	if (HasAuthority())
	{
		gm = Cast<APlayerGameMode>( GetWorld()->GetAuthGameMode() );
		GameStartTime = GetWorld()->GetTimeSeconds(); // 게임 시작 시간 기록
		OnRep_GameStartTime();
	}
}

void ATarKOVPlayerController::UpdatekillCnt(int32 killOtherPlayer)
{
	// **Player takeDamage 함수에서 hp == 0 일 떄, 해당 함수 호출 (함수 매개변수로 캐릭터 변수 추가)
	// fireComp 에서 takedamage 호출 할 때, me로 넘겨줌
	// **만약 takedamage 함수에서 hp == 0이라 죽으면 me->getcontroller()->UpdatekillCnt(1); 해줌

	// killCnt++
	killCnt += killOtherPlayer;

	// 위젯 변수를 여기서 추가하든, 위젯에서 controller 정의하고 controller의 killCnt 값 가져와서 셋팅하던 

}

void ATarKOVPlayerController::OnRep_GameStartTime()
{
}

void ATarKOVPlayerController::CalculatePlayTime()
{
	if (GetWorld())
	{
		PlayTime = GetWorld()->GetTimeSeconds() - GameStartTime;
	}
}


void ATarKOVPlayerController::ServerRetry_Implementation()
{
	//이곳은 서버에서 호출되는 함수이다.
	// 재시작 요청이 오면
	// 현재 캐릭터를 기억하고
	auto character = this->GetPawn();
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

void ATarKOVPlayerController::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ATarKOVPlayerController , GameStartTime );
	DOREPLIFETIME( ATarKOVPlayerController , PlayTime );

}