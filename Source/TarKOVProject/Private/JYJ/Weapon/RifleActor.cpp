// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Weapon/RifleActor.h"

// Sets default values
ARifleActor::ARifleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh( TEXT( "/Script/Engine.SkeletalMesh'/Game/TarKOV/JYJ/Models/Weapons/Meshes/Ka47/SK_KA47.SK_KA47'" ) );
	if (tmpMesh.Succeeded())
	{
		meshComp->SetSkeletalMesh( tmpMesh.Object );
		meshComp->SetRelativeLocation( FVector( 3 , -1 , 2 ) );
		//(Pitch=40.000000,Yaw=-100.000000,Roll=80.000000)
		meshComp->SetRelativeRotation( FRotator( 40 , -100 , 80 ) );
		meshComp->SetWorldScale3D( FVector( 1.5f ) );
	}


}

// Called when the game starts or when spawned
void ARifleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARifleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

