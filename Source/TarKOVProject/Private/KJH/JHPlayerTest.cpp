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

	InitUI();
}

void AJHPlayerTest::PossessedBy( AController* NewController )
{
	Super::PossessedBy( NewController );

	InitUI();
}

void AJHPlayerTest::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>( PlayerInputComponent );

	//SetupInputDelegate.Broadcast( input );
}

void AJHPlayerTest::OnHitboxOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
	UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	Super::OnHitboxOverlap( OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep , SweepResult );
}

void AJHPlayerTest::InitUI()
{
	// 컨트롤러가 PlayerController가 아니라면 함수를 바로 종료
    // 즉, mainUI를 생성하지 않겠다.
	auto pc = Cast<ATarKOVPlayerController>( Controller );
	if (nullptr == pc)
	{
		UE_LOG( LogTemp , Warning , TEXT( "%s : nullptr == pc" ) , __FUNCTION__ );
		return;
	}
	if (false == IsLocallyControlled())
	{
		UE_LOG( LogTemp , Warning , TEXT( "%s : false == IsLocallyControlled()" ) , __FUNCTION__ );
		return;
	}

	UE_LOG( LogTemp , Warning , TEXT( "AJHPlayerTest::InitUI" ) );


	if (nullptr == pc->PlayerMainUI)
	{
		// MainUI를 생성해서 기억하고싶다.
		pc->PlayerMainUI = CreateWidget<UHPWidget>( GetWorld() , pc->PlayerMainUIFactory );
		// AddToViewport하고싶다.
		pc->PlayerMainUI->AddToViewport();
	}

	// 만들어진 mainUI를 기억하고싶다.
	PlayerMainUI = pc->PlayerMainUI;
	// 만들어진 GameOVerUI를 기억하고싶다.
	GameOverUI = pc->GameOverUI;

	PlayerMainUI = pc->PlayerMainUI;



	//// 각각 함수를 따로 만들어 두어야 할까?

	//// 플레이어가 죽으면 gameoverui가 뜨게하고 싶다.
	//if (nullptr == pc->GameOverUI) //&& 플레이어가 죽었을때
	//{
	//	// GameOverUI를 생성해서 기억하고싶다.
	//	pc->GameOverUI = CreateWidget<UGameOverWidget>( GetWorld() , pc->GameOverUIFactory );
	//	// AddToViewport하고싶다.
	//	pc->GameOverUI->AddToViewport();

	//}
	//// 만들어진 PlayerMainUI를 기억하고싶다.
	//GameOverUI = pc->GameOverUI;


	//// 플레이어가 트리거에서 5초 지나면 gameclearui가 뜨게 하고 싶다.
	//if (nullptr == pc->GameClearUI) //&& 플레이어가 죽었을때
	//{
	//	// GameOverUI를 생성해서 기억하고싶다.
	//	pc->GameClearUI = CreateWidget<UGameClearWidget>( GetWorld() , pc->GameClearUIFactory );
	//	// AddToViewport하고싶다.
	//	pc->GameClearUI->AddToViewport();

	//}
	//// 만들어진 PlayerMainUI를 기억하고싶다.
	//GameClearUI = pc->GameClearUI;
}

void AJHPlayerTest::DamageProcess()
{
	// 죽음 애니메이션이 끝나면
    // 마우스 커서를 보이게하고싶다.
	auto pc = Cast<ATarKOVPlayerController>( Controller );
	pc->SetShowMouseCursor( true );
	// 화면을 회색으로 보이게 하고싶다.
	FollowCamera->PostProcessSettings.ColorSaturation = FVector4( 0 , 0 , 0 , 1 );
	// 게임오버UI를 보이게하고싶다.
	if (nullptr == pc->GameOverUI)
	{
		// GameOverUI를 생성해서 기억하고싶다.
		pc->GameOverUI = CreateWidget<UGameOverWidget>( GetWorld() , pc->GameOverUIFactory );
		// AddToViewport하고싶다.
		pc->GameOverUI->AddToViewport();
	}
}

