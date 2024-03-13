// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Weapon/PistolGun.h"

#include "Net/UnrealNetwork.h"

APistolGun::APistolGun()
{
	PrimaryActorTick.bCanEverTick = true;

	pistolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pistolMesh"));
	SetRootComponent(pistolMesh);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpMesh( TEXT( "/Script/Engine.StaticMesh'/Game/TarKOV/JYJ/Models/PistolMesh/Textures/SM_Pistol.SM_Pistol'" ) );
	if (tmpMesh.Succeeded())
	{
		pistolMesh->SetStaticMesh( tmpMesh.Object );
		pistolMesh->SetWorldScale3D( FVector( 1.1f ) );
		//GunMeshComp->SetRelativeRotation( FRotator( 40 , -100 , 80 ) );
	}

	AimCamSocket->SetupAttachment(RootComponent);
	AimCamSocket->SetRelativeLocation( FVector( 0 , -5 , 10 ) );
	AimCamSocket->SetRelativeRotation( FRotator( 0 , 90 , 0 ) );

	pistolMesh->SetIsReplicated( true );

}

void APistolGun::BeginPlay()
{
	Super::BeginPlay();

	//pistol CP Setting
	gunCP = 2.0f;

	//pistol 탄피 (test용으로 10개 셋팅)
	gunMaxAmmo = 30;
	currentAmmo = gunMaxAmmo;

	bEnableRepeating = false;
}

void APistolGun::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( APistolGun , currentAmmo );
}
