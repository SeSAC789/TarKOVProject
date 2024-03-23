// Fill out your copyright notice in the Description page of Project Settings.

#include "JYJ/PlayerComp/PlayerThrowComp.h"

#include <iso646.h>

#include "JYJ/Animation/PlayerAnimInstance.h"
#include "JYJ/PlayerBase.h"
#include "KJH/HealthComp.h"
#include "JYJ/Weapon/BombBase.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UPlayerThrowComp::UPlayerThrowComp()
{
	SetIsReplicatedByDefault( true );
}

void UPlayerThrowComp::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnim = Cast<UPlayerAnimInstance>( me->GetMesh()->GetAnimInstance() );
	check( PlayerAnim );
}

void UPlayerThrowComp::SetupInput(UEnhancedInputComponent* input)
{
	Super::SetupInput( input );

	if (nullptr == input) return;

	// Bomb
	input->BindAction( BombThrowAction , ETriggerEvent::Started , this , &UPlayerThrowComp::InputThrow );
}

void UPlayerThrowComp::InputThrow()
{
	ServerRPCThrowBomb();
	//PlayerAnim->playGrenadeAnimation();
}

void UPlayerThrowComp::throwBomb()
{
	
	SpawnGrenade( BombBase );

	//ServerRPCThrowBomb();
	
}

void UPlayerThrowComp::ServerRPCTSpawnBomb_Implementation( TSubclassOf<ABombBase> BombFactory )
{
	if (!me) { return; }

	if (BombFactory)
	{
		MultiRPCSpawnBomb( BombFactory );
	}
}

void UPlayerThrowComp::MultiRPCSpawnBomb_Implementation( TSubclassOf<ABombBase> BombFactory )
{
	grenade = GetWorld()->SpawnActor<ABombBase>( BombFactory , me->GetActorLocation() , me->GetActorRotation() );
	if (grenade)
	{
		UE_LOG( LogTemp , Warning , TEXT( "UPlayerThrowComp::SpawnGrenade - Success" ) )
			grenade->AttachToComponent( me->pistolComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
		grenade->SetOwner( me );


		/*
		FTimerHandle handler;
		GetWorld()->GetTimerManager().SetTimer( handler , [&]()
		{
			grenade->TakeDamageBomb();

		} , 5 , false );
		*/


	}
	//ServerRPCSpawnPistol(GunFactory)
}


void UPlayerThrowComp::SpawnGrenade( TSubclassOf<ABombBase> BombFactory )
{
	ServerRPCTSpawnBomb( BombFactory );
}

void UPlayerThrowComp::ServerRPCThrowBomb_Implementation( )
{
	//PlayerAnim->playGrenadeAnimation();
	//selectedBomb->ExplosiveBomb(selectedBomb);
	MultiRPCThrowBomb();
}

void UPlayerThrowComp::MultiRPCThrowBomb_Implementation()
{
	PlayerAnim->playGrenadeAnimation();
}


void UPlayerThrowComp::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UPlayerThrowComp , grenade );
}
