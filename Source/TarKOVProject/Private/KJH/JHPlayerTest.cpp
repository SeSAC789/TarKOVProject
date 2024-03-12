// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/JHPlayerTest.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "KJH/HealthComp.h"
#include "KJH/HPWidget.h"
#include "Blueprint/UserWidget.h"

AJHPlayerTest::AJHPlayerTest()
{
	
}

void AJHPlayerTest::BeginPlay()
{
	Super::BeginPlay();

	if (!hpUI)
	{
		// MainUI를 생성해서 기억하고싶다.
		hpUI = CreateWidget<UHPWidget>( GetWorld() , hpUIFactory );
		// AddtoViewport하고싶다.
		hpUI->AddToViewport();
	}

}

void AJHPlayerTest::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>( PlayerInputComponent );

	SetupInputDelegate.Broadcast( input );
}

void AJHPlayerTest::OnHitboxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnHitboxOverlap(OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep , SweepResult);
}


