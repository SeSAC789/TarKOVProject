// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Weapon/TraceActor.h"

// Sets default values
ATraceActor::ATraceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpMesh( TEXT( "/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'" ) );
	if (tmpMesh.Succeeded())
	{
		meshComp->SetStaticMesh( tmpMesh.Object );
		meshComp->SetWorldScale3D( FVector( 0.5f ) );
		meshComp->SetRelativeRotation( FRotator( 0 , 0 , 90 ) );
	}


}

// Called when the game starts or when spawned
void ATraceActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATraceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

