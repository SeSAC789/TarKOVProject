// Fill out your copyright notice in the Description page of Project Settings.

#include "JYJ/PlayerComp/PlayerThrowComp.h"
#include "JYJ/Animation/PlayerAnimInstance.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/Weapon/BombBase.h"
#include "EnhancedInputComponent.h"

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
	input->BindAction( BombThrowAction , ETriggerEvent::Started , this , &UPlayerThrowComp::throwBomb );
}

void UPlayerThrowComp::throwBomb()
{
	SpawnGrenade( BombBase);

	FTimerHandle handler;
	GetWorld()->GetTimerManager().SetTimer( handler , [&]()
	{
		grenade->explosiveBomb();

	} , 5 , false );
	
}


void UPlayerThrowComp::SpawnGrenade( TSubclassOf<ABombBase> BombFactory )
{
	if (!me) { return; }

	if (BombFactory)
	{
		grenade = GetWorld()->SpawnActor<ABombBase>( BombFactory , me->GetActorLocation() , me->GetActorRotation() );

		if (grenade)
		{
			UE_LOG(LogTemp, Warning, TEXT("UPlayerThrowComp::SpawnGrenade - Success"))
			//OnRep_Pistol();
		}
		//ServerRPCSpawnPistol(GunFactory);

	}
}
