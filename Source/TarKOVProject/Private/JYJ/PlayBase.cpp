// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayBase::APlayBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(GetCapsuleComponent()); 
	springArmComp->SetWorldLocation(FVector( 0, 0, 90));

	camComp = CreateDefaultSubobject<UCameraComponent>(TEXT("camComp"));
	camComp->SetupAttachment(springArmComp);
	camComp->SetWorldLocation(FVector(0, 40, 0 ));


}

// Called when the game starts or when spawned
void APlayBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayBase::OnAxisVertical( float value )
{
}

void APlayBase::OnAxisHorixontal( float value )
{
}

void APlayBase::OnAxisTurnYaw(float value)
{
}

void APlayBase::OnAxisTurnPitch(float value)
{
}

void APlayBase::OnActionJump()
{
}

void APlayBase::Sprint()
{
}

void APlayBase::StopSprinting()
{
}


