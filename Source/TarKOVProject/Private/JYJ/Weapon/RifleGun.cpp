// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Weapon/RifleGun.h"

#include "JYJ/Weapon/PistolGun.h"
#include "Net/UnrealNetwork.h"

ARifleGun::ARifleGun()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh( TEXT( "/Script/Engine.SkeletalMesh'/Game/TarKOV/JYJ/Models/Weapons/Meshes/Ka47/SK_KA47.SK_KA47'" ) );
	if (tmpMesh.Succeeded())
	{
		GunMeshComp->SetSkeletalMesh( tmpMesh.Object );
		GunMeshComp->SetWorldScale3D( FVector( 0.8f ) );
		//GunMeshComp->SetRelativeRotation( FRotator( 40 , -100 , 80 ) );
	}

	AimCamSocket->SetRelativeLocation( FVector( 0 , 15 , 20 ) );
	AimCamSocket->SetRelativeRotation( FRotator( 0 , 90 , 0 ) );

	GunMeshComp->SetIsReplicated(true);
}

void ARifleGun::BeginPlay()
{
	Super::BeginPlay();

	//rifle CP Setting
	gunCP = 5.0f;

	//rifle 탄피 (test용으로 10개 셋팅)
	gunMaxAmmo = 30;

	currentAmmo = gunMaxAmmo;

	bEnableRepeating = true;
}

void ARifleGun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( ARifleGun , currentAmmo );
}

