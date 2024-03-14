// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/TestPlayer/YJTestPlayer.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "KJH/HPWidget.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "JYJ/PlayerComp/PlayerMoveComp.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "JYJ/PlayerComp/PlayerFireComp.h"

AYJTestPlayer::AYJTestPlayer()
{
	
}

void AYJTestPlayer::BeginPlay()
{
	Super::BeginPlay();

	
	if (!hpUI)
	{
		// MainUI를 생성해서 기억하고싶다.
		hpUI = CreateWidget<UHPWidget>( GetWorld() , hpUIFactory );
		// AddtoViewport하고싶다.
		if(hpUI)
		{
			hpUI->AddToViewport();
		}
		
	}

}

void AYJTestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>( PlayerInputComponent );

	SetupInputDelegate.Broadcast( input );
	//moveComp1->SetupInput( input );
}

void AYJTestPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AYJTestPlayer* NewCharacter = Cast<AYJTestPlayer>( NewController->GetCharacter() ))
	{
		if (!NewCharacter->fireComp)
		{
			UE_LOG( LogTemp , Warning , TEXT( "APlayerGameMode::OnPostLogin - No FireComp" ) )
			return;
		}

		NewCharacter->fireComp->SpawnRifle( NewCharacter->fireComp->RifleGun );
		NewCharacter->fireComp->SpawnPistol( NewCharacter->fireComp->PistolGun );

		//NewCharacter->fireComp->OnRep_Pistol();
		//NewCharacter->fireComp->OnRep_Rifle();
		//NewCharacter->fireComp->ServerRPCSpawnRifle( NewCharacter->fireComp->RifleGun );
		//NewCharacter->fireComp->bValidRifle = false;
		//NewCharacter->fireComp->On_Rep_Rifle();

		/*NewCharacter->fireComp->ServerRPCSpawnPistol( NewCharacter->fireComp->PistolGun */
		

	}
	else
	{
		UE_LOG( LogTemp , Warning , TEXT( "APlayerGameMode::OnPostLogin - No Character" ) )
	}
}

