// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Weapon/RifleActor.h"

#include "Camera/CameraComponent.h"

// Sets default values
ARifleActor::ARifleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("meshComp"));
	SetRootComponent(meshComp);

	//Rifle Cam Settings
	rifleCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("rifleCamComp"));
	rifleCamComp->SetupAttachment(meshComp);
	rifleCamComp->SetRelativeLocation(FVector( 0, -12.691425 , 14.088460 ));
	rifleCamComp->SetRelativeRotation(FRotator( 2.248205 , 90, 0));

	rifleCamSocket = CreateDefaultSubobject<USceneComponent>(TEXT("rifleCamSocket"));
	rifleCamSocket->SetupAttachment( meshComp );
	rifleCamSocket->SetRelativeLocation( FVector( 0.170610 , -2.909110 , 17.945868 ) );
	rifleCamSocket->SetRelativeRotation( FRotator( 0 , 90 , 0 ) );

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh( TEXT( "/Script/Engine.SkeletalMesh'/Game/TarKOV/JYJ/Models/Weapons/Meshes/Ka47/SK_KA47.SK_KA47'" ) );
	if (tmpMesh.Succeeded())
	{
		meshComp->SetSkeletalMesh( tmpMesh.Object );
		meshComp->SetWorldScale3D( FVector( 1.1f ) );
		meshComp->SetRelativeRotation( FRotator( 40 , -100 , 80 ) );
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

void ARifleActor::ActiveRifleCamp(bool isRifle, APlayerController* controller )
{
	if(false == isRifle) return;

	rifleCamComp->Activate(true);
	controller->SetViewTargetWithBlend(this);
}

void ARifleActor::DeactiveRifleCamp()
{
	rifleCamComp->Deactivate();
}

