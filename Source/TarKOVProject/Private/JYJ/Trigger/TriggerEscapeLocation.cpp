// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Trigger/TriggerEscapeLocation.h"
#include "GPUMessaging.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "JYJ/UI/GameClearWidget.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/Controller/TarKOVPlayerController.h"

ATriggerEscapeLocation::ATriggerEscapeLocation()
{
	// Collision Setting
	TriggerBox->OnComponentBeginOverlap.AddDynamic( this , &ATriggerEscapeLocation::OnTriggerBoxOverlap );
	TriggerBox->OnComponentEndOverlap.AddDynamic( this , &ATriggerEscapeLocation::OnTriggerBoxEndOverlap );


	bReplicates = true;
}

void ATriggerEscapeLocation::OnTriggerBoxOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
												 UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	APlayerBase* Player = Cast<APlayerBase>( OtherActor );
	if (!Player)
	{
		return;
	}

	if (!Player->IsLocallyControlled())
	{
		return;
	}
	Super::OnTriggerBoxOverlap( OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep ,
							   SweepResult );

	GetWorld()->GetTimerManager().SetTimer( GameClearTimerHandle , this , &ATriggerEscapeLocation::GameClearTimerFinished , 7.0f , false );

	auto pc = Cast<ATarKOVPlayerController>( GetWorld()->GetFirstPlayerController() );
	if (pc)
	{
		// UI 표시
		pc->ShowEscapeUI( true );
	}
	// 오버랩 이벤트가 서버에서 발생했는지 확인
   // DisplayGameClearUI(OtherActor);
}

void ATriggerEscapeLocation::OnTriggerBoxEndOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
	UPrimitiveComponent* OtherComp , int32 OtherBodyIndex )
{
	APlayerBase* Player = Cast<APlayerBase>( OtherActor );
	if (!Player)
	{
		return;
	}

	if (!Player->IsLocallyControlled())
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer( GameClearTimerHandle );

	auto pc = Cast<ATarKOVPlayerController>( GetWorld()->GetFirstPlayerController() );
	if (pc)
	{
		// UI 숨기기
		pc->ShowEscapeUI( false );
	}
}

void ATriggerEscapeLocation::DisplayGameClearUI( AActor* InOverlapActor )
{
	APlayerBase* me = Cast<APlayerBase>( InOverlapActor );
	if (!me)
	{
		return;
	}

	if (!me->IsLocallyControlled())
	{
		return;
	}
	// 클라이언트에 UI 표시 요청
	//ClientDisplayGameClearUI();
	auto pc = Cast<ATarKOVPlayerController>( GetWorld()->GetFirstPlayerController() );
	if (!pc)
	{
		return;
	}

	pc->GameClearUI = CreateWidget<UGameClearWidget>( GetWorld() , pc->GameClearUIFactory );
	if (!pc->GameClearUI)
	{
		return;
	}


	pc->CalculateAndSavePlayTime(); // 플레이 타임 계산 및 저장

	pc->GameClearUI->AddToViewport();
	pc->GameClearUI->SetPlayTime( pc->PlayerPlayTime ); // UI에 플레이 타임 설정
	pc->SetShowMouseCursor( true );

	pc->DisableInput( pc );
	me->OnDeath();




}

void ATriggerEscapeLocation::GameClearTimerFinished()
{
	DisplayGameClearUI( GetWorld()->GetFirstPlayerController()->GetPawn() );
}
