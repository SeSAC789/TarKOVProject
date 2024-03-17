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

}

void ATriggerEscapeLocation::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnTriggerBoxOverlap(OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep ,
	                           SweepResult);

	// Test Mission Sucess UI
	if(OtherActor == Cast<APlayerBase>(OtherActor))
	{
		FTimerHandle handler;
		GetWorld()->GetTimerManager().SetTimer( handler , [&]()
		{
				GameClearUI = CreateWidget<UGameClearWidget>(GetWorld(), GameClearUIFactory);
				GameClearUI->AddToViewport();

				auto pc = GetWorld()->GetFirstPlayerController();
				pc->SetShowMouseCursor( true );

				//10초 뒤, 탈출 Log 출력
				UE_LOG( LogTemp , Warning , TEXT( "ATriggerEscapeLocation::OnTriggerBoxOverlap" ) )

		} , 5, false );

	}

}
