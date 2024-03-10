// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Animation/PlayerAnimInstance.h"
#include "JYJ/PlayerComp/PlayerMoveComp.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/PlayerComp/PlayerFireComp.h"
#include "JYJ/TestPlayer/YJTestPlayer.h"
#include "KJH/HealthComp.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//1. owner pawn 을 가져와서 atpsplayer 로 cast 하고 싶다.
	APlayerBase* player = Cast<APlayerBase>( TryGetPawnOwner() );

	if (nullptr == player )
		return;

	
	//2. 오너의 velocity, forwward vector, right vector를 가져오고 싶다.
	FVector v = player->GetVelocity();
	FVector forward = player->GetActorForwardVector();
	FVector right = player->GetActorRightVector();

	//3. speed, direcition 의 값을 채우고 싶다.
	speed = FVector::DotProduct( v , forward );
	direction = FVector::DotProduct( v , right );

	//4. isInAir, isCrouch를 채우고 싶다.
	isInAir = player->GetCharacterMovement()->IsFalling();
	isCrouched = player->moveComp->isCrouched;
	isProned = player->moveComp->isProned;

	bAimRifle = player->fireComp->bAimRifle;
	bValidRifle = player->fireComp->bValidRifle;
	bValidPistol = player->fireComp->bValidPistol;

	pitch = player->GetBaseAimRotation().GetNormalized().Pitch;
	pitch = FMath::Clamp(pitch, -90, 90);
	yaw = player->GetBaseAimRotation().Yaw;
	roll = player->GetBaseAimRotation().Roll;

	isDie = player->HealthComp->bIsDead;

}

void UPlayerAnimInstance::playFireAnimation()
{
	Montage_Play( fireRifleMontage );
	UE_LOG(LogTemp, Warning, TEXT("Anim TEST"));
}
