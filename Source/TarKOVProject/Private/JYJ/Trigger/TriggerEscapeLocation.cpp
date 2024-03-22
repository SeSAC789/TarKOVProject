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

    bReplicates = true;
}

void ATriggerEscapeLocation::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnTriggerBoxOverlap(OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep ,
	                           SweepResult);

    // 오버랩 이벤트가 서버에서 발생했는지 확인
    DisplayGameClearUI(OtherActor);
}

void ATriggerEscapeLocation::DisplayGameClearUI( AActor* InOverlapActor )
{
    APlayerBase* Player = Cast<APlayerBase>( InOverlapActor );
    if (!Player)
    {
        return;
    }

    if (!Player->IsLocallyControlled())
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

    pc->GameClearUI->AddToViewport();
    pc->SetShowMouseCursor( true );

}
