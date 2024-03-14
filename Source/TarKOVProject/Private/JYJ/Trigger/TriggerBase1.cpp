// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Trigger/TriggerBase1.h"

// Sets default values
ATriggerBase1::ATriggerBase1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATriggerBase1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerBase1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

