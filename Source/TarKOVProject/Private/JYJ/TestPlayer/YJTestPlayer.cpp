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
	/*
	springComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springComp"));
	springComp->SetupAttachment(GetMesh());

	springComp->SetRelativeLocation( FVector( 0 , 20 , 160 ) );
	springComp->SetRelativeRotation( FRotator( 0 , 90 , 0 ) );
	springComp->TargetArmLength = 0;

	FollowCamera->SetupAttachment(springComp);
	*/
	

	moveComp1 = CreateDefaultSubobject<UPlayerMoveComp>(TEXT("moveComp1"));
	fireComp = CreateDefaultSubobject<UPlayerFireComp>(TEXT("fireComp"));

	GetCharacterMovement()->MaxWalkSpeedCrouched = 180.0f;
}

void AYJTestPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>( PlayerInputComponent );

	SetupInputDelegate.Broadcast( input );
	//moveComp1->SetupInput( input );
}
