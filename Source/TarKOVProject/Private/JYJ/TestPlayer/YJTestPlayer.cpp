// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/TestPlayer/YJTestPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "JYJ/PlayerComp/PlayerMoveComp.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "JYJ/PlayerComp/PlayerFireComp.h"

AYJTestPlayer::AYJTestPlayer()
{

}

void AYJTestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>( PlayerInputComponent );

	SetupInputDelegate.Broadcast( input );
	//moveComp1->SetupInput( input );
}
