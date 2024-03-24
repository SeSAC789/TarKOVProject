// Fill out your copyright notice in the Description page of Project Settings.

#include "JYJ/Weapon/BombBase.h"
#include "JYJ/PlayerBase.h"
#include "EngineUtils.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JYJ/Controller/TarKOVPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "KJH/HealthComp.h"
#include "Net/UnrealNetwork.h"

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

		//GrenadeMesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	}

	if (!throwDir)
	{
		// 이 컴포넌트를 사용하여 이 발사체의 이동을 주도합니다.
		throwDir = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT( "ProjectileMovementComponent" ) );
		//throwDir->SetUpdatedComponent();
		throwDir->InitialSpeed = 800.0f;
		throwDir->MaxSpeed = 8000.0f;
		//throwDir->bRotationFollowsVelocity = true;
		throwDir->bShouldBounce = false;
		throwDir->Bounciness = 0.3f;
		throwDir->ProjectileGravityScale = 0.0f;
	}

	GrenadeMesh->SetSimulatePhysics(true);
	GrenadeMesh->SetIsReplicated( true );


}

// Called when the game starts or when spawned
void ABombBase::BeginPlay()
{
	Super::BeginPlay();

	if(!bombSFX && !bombVFX)	return;

	FTimerHandle handler;
	GetWorld()->GetTimerManager().SetTimer( handler , [&]()
	{
		// 가까운 플레이어를 검색
		StartTrace = this->GetActorLocation();
		EndTrace = StartTrace + (FVector::UpVector * detectRadius); // 검색 반경 설정

		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere( detectRadius );

		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex = true;
		QueryParams.AddIgnoredActor( this ); // 폭탄 자신을 무시

		bool bHits = GetWorld()->SweepMultiByChannel( HitResults , StartTrace , EndTrace , FQuat::Identity , ECC_Pawn , CollisionShape , QueryParams );

		if (bHits)
		{
			TSet<AActor*> DamagedPlayers;

			for (auto& HitResult : HitResults)
			{
				AActor* HitActor = HitResult.GetActor();
				if (HitActor && HitActor->IsA<APlayerBase>())
				{
					APlayerBase* Player = Cast<APlayerBase>( HitActor );
					if (Player && !DamagedPlayers.Contains( Player ))
					{
						if (Player)
						{
							FString HitObjectName = Player->GetName();
							Player->HealthComp->TakeDamage( 30 , HitObjectName );
							UE_LOG( LogTemp , Warning , TEXT( "Bomb Damage Test3" ) );

							DamagedPlayers.Add( Player );
						}
					}
				}
			}

			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , bombVFX , this->GetActorLocation() );
			UGameplayStatics::PlaySound2D( GetWorld() , bombSFX );
			this->Destroy();
		}

	} , 5 , false );
}

// Called every frame
void ABombBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//DrawDebugSphere( GetWorld() , GetActorLocation() , detectRadius , 32 , FColor::Cyan , false , 0 );
}


void ABombBase::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ABombBase , playerTarget );
	DOREPLIFETIME( ABombBase , HitResults );
	DOREPLIFETIME( ABombBase , StartTrace );
	DOREPLIFETIME( ABombBase , EndTrace );

}
