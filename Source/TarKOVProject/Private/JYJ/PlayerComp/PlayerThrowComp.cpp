// Fill out your copyright notice in the Description page of Project Settings.

#include "JYJ/PlayerComp/PlayerThrowComp.h"

#include <iso646.h>

#include "JYJ/Animation/PlayerAnimInstance.h"
#include "JYJ/PlayerBase.h"
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
	
	FTimerHandle handler;
	GetWorld()->GetTimerManager().SetTimer( handler , [&]()
	{
		grenade->TakeDamageBomb(grenade);
		//ServerRPCThrowBomb(grenade);

	} , 5 , false );
	
	//ServerRPCThrowBomb();
	
}


void UPlayerThrowComp::SpawnGrenade( TSubclassOf<ABombBase> BombFactory )
{
	if (!me) { return; }

	if (BombFactory)
	{
		grenade = GetWorld()->SpawnActor<ABombBase>( BombFactory , me->GetActorLocation() , me->GetActorRotation() );
		//grenade = GetWorld()->SpawnActor<ABombBase>( BombFactory , FVector::ZeroVector , FRotator::ZeroRotator );

		if (grenade)
		{
			UE_LOG(LogTemp, Warning, TEXT("UPlayerThrowComp::SpawnGrenade - Success"))
			grenade->AttachToComponent( me->pistolComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
			grenade->SetOwner( me );
			//OnRep_Bomb();
		}
		//ServerRPCSpawnPistol(GunFactory);

	}
}

void UPlayerThrowComp::ServerRPCThrowBomb_Implementation( )
{
	PlayerAnim->playGrenadeAnimation();
	//selectedBomb->ExplosiveBomb(selectedBomb);
	//MultiRPCThrowBomb( selectedBomb );
	
	
}

void UPlayerThrowComp::MultiRPCThrowBomb_Implementation( ABombBase* selectedBomb )
{
	//UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , ExplosionVFXFactory , selectedBomb->GetActorLocation() );
}

void UPlayerThrowComp::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UPlayerThrowComp , grenade );
}
