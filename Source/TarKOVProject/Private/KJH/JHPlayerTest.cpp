// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/JHPlayerTest.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "KJH/HealthComp.h"
#include "KJH/HPWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/PostProcessComponent.h"
#include "JYJ/Controller/TarKOVPlayerController.h"
#include "JYJ/GameOverWidget.h"

AJHPlayerTest::AJHPlayerTest()
{
	
}

void AJHPlayerTest::BeginPlay()
{
	Super::BeginPlay();

	//if (!PlayerMainUI)
	//{
	//	 //MainUI를 생성해서 기억하고싶다.
	//	PlayerMainUI = CreateWidget<UHPWidget>( GetWorld() , PlayerMainUIFactory );
	//	// AddtoViewport하고싶다.
	//	PlayerMainUI->AddToViewport();
	//}


}

void AJHPlayerTest::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>( PlayerInputComponent );

	//SetupInputDelegate.Broadcast( input );
}

void AJHPlayerTest::OnHitboxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnHitboxOverlap(OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep , SweepResult);
}

void AJHPlayerTest::InitUI()
{
	auto pc = Cast<ATarKOVPlayerController>( GetController() );

	if (nullptr == pc->PlayerMainUI)
	{
		// PlayerMainUI를 생성해서 기억하고싶다.
		pc->PlayerMainUI = CreateWidget<UHPWidget>( GetWorld() , pc->PlayerMainUIFactory );
		// AddToViewport하고싶다.
		pc->PlayerMainUI->AddToViewport();
		
	}
	// 만들어진 PlayerMainUI를 기억하고싶다.
	PlayerMainUI = pc->PlayerMainUI;



	// 각각 함수를 따로 만들어 두어야 할까?

	// 플레이어가 죽으면 gameoverui가 뜨게하고 싶다.
	if (nullptr == pc->GameOverUI) //&& 플레이어가 죽었을때
	{
		// GameOverUI를 생성해서 기억하고싶다.
		pc->GameOverUI = CreateWidget<UGameOverWidget>( GetWorld() , pc->GameOverUIFactory );
		// AddToViewport하고싶다.
		pc->GameOverUI->AddToViewport();

	}
	// 만들어진 PlayerMainUI를 기억하고싶다.
	GameOverUI = pc->GameOverUI;


	// 플레이어가 트리거에서 5초 지나면 gameclearui가 뜨게 하고 싶다.
	if (nullptr == pc->GameClearUI) //&& 플레이어가 죽었을때
	{
		// GameOverUI를 생성해서 기억하고싶다.
		pc->GameClearUI = CreateWidget<UGameClearWidget>( GetWorld() , pc->GameClearUIFactory );
		// AddToViewport하고싶다.
		pc->GameClearUI->AddToViewport();

	}
	// 만들어진 PlayerMainUI를 기억하고싶다.
	GameClearUI = pc->GameClearUI;
}

