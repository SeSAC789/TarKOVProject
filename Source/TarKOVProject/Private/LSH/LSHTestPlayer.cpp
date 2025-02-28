﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH/LSHTestPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "JYJ/PlayerComp/PlayerMoveComp.h"
#include "LSH/InvnetoryWidget.h"
#include "GameFramework/CharacterMovementComponent.h"

ALSHTestPlayer::ALSHTestPlayer()
{
	moveComp1 = CreateDefaultSubobject<UPlayerMoveComp>( TEXT( "moveComp1" ) );

	GetCharacterMovement()->MaxWalkSpeedCrouched = 180.0f;
}

void ALSHTestPlayer::BeginPlay()
{
	Super::BeginPlay();


}

void ALSHTestPlayer::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>( PlayerInputComponent );

	SetupInputDelegate.Broadcast( input );
	//moveComp1->SetupInput( input );
}

 