// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Trigger/TriggerBase1.h"

#include "Components/BoxComponent.h"

// Sets default values
ATriggerBase1::ATriggerBase1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	TriggerBox->SetWorldScale3D(FVector(2.0f));


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

void ATriggerBase1::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

