// Fill out your copyright notice in the Description page of Project Settings.

#include "JYJ/Weapon/BombBase.h"
#include "JYJ/PlayerBase.h"
#include "EngineUtils.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "KJH/HealthComp.h"

// Sets default values
ABombBase::ABombBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "GrenadeMesh" ) );
	SetRootComponent( GrenadeMesh );

	ConstructorHelpers::FObjectFinder<UStaticMesh> tmpMesh( TEXT( "/Script/Engine.StaticMesh'/Game/TarKOV/JYJ/Models/Weapons/Meshes/G67_Grenade/SM_G67.SM_G67'" ) );
	if (tmpMesh.Succeeded())
	{
		GrenadeMesh->SetStaticMesh( tmpMesh.Object );
		GrenadeMesh->SetWorldScale3D( FVector( 1.1f ) );

		GrenadeMesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	}

	if (!throwDir)
	{
		// 이 컴포넌트를 사용하여 이 발사체의 이동을 주도합니다.
		throwDir = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT( "ProjectileMovementComponent" ) );
		//throwDir->SetUpdatedComponent();
		throwDir->InitialSpeed = 3000.0f;
		throwDir->MaxSpeed = 3000.0f;
		throwDir->bRotationFollowsVelocity = true;
		throwDir->bShouldBounce = true;
		throwDir->Bounciness = 0.3f;
		throwDir->ProjectileGravityScale = 0.0f;
	}


}

// Called when the game starts or when spawned
void ABombBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABombBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABombBase::explosiveBomb()
{
	DrawDebugSphere( GetWorld() , GetActorLocation() , detectRadius , 32 , FColor::Cyan , false , 0 );

	//레벨에 있는 ANetTPSCharacter 객체들을 다 검사해서 detectRadius안에 있고 그중에서도 가장 가까운 녀석을 내 오너로 하고 싶다.
	if (HasAuthority())	//서버
	{
		AActor* newOwner = nullptr;
		float tmpDist = detectRadius;
		for (TActorIterator<APlayerBase> It( GetWorld() ); It; ++It)
		{
			APlayerBase* player = *It;

			// TakeDamage 하는 동작 필요

			//FName BodyPart = HitComp->ComponentTags[0];
			//FString HitObjectName = OutHit.GetComponent()->GetName();

			//player->HealthComp->TakeDamage()
			//상대방과 나의 거리를 측정해서 tempDist보다 가깝다면 newOwner로 기억하고 싶다
			/*
			float temp = player->GetDistanceTo( this );
			if (temp < tmpDist)
			{
				newOwner = player;
				//tempDist 값을 계속 갱신해주면서 비교
				tmpDist = temp;
			}
			*/

		}

	}
}

