// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/Medikit.h"
#include "KJH/HealthComp.h"
#include "Components/BoxComponent.h"
#include "JYJ/PlayerBase.h"
#include "KJH/HealthComp.h"

AMedikit::AMedikit()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
	this->SetRootComponent( BoxComp );
	BoxComp->InitBoxExtent( FVector( 5.0f , 5.0f , 5.0f ) );

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
	MeshComp->SetupAttachment( RootComponent );

	BoxComp->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
	BoxComp->SetCollisionResponseToAllChannels( ECR_Overlap );
	MeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

void AMedikit::BeginPlay() 
{
	Super::BeginPlay();
	
	//player = Cast<APlayerBase>( GetOwner() );
	//healthComp = Cast<UHealthComp>( player->GetComponentByClass( UHealthComp::StaticClass() ) );
}

void AMedikit::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	
	APlayerBase* Player = Cast<APlayerBase>( OtherActor );
	if (Player)
	{
		UHealthComp* HealthComp = Cast<UHealthComp>( Player->GetComponentByClass( UHealthComp::StaticClass() ) );
		if (HealthComp)
		{
			// 모든 부위를 검사하여 다친 부위를 회복
			TArray<FName> InjuredParts = HealthComp->GetInjuredBodyParts();
			for (const FName& InjuredPart : InjuredParts)
			{
				if (HealthComp->IsInjured( InjuredPart ))
				{
					HealthComp->HealBodyPart( InjuredPart , 25.0f );
				}
			}

			//// 메디킷 사용 후 파괴
			//Destroy();
		}
	}
}

void AMedikit::RecoveryHP(AActor* OverlappedActor, FName OverlappedBodyPart)
{
	if (!OverlappedActor)
	{
		return;
	}

	APlayerBase* Player = Cast<APlayerBase>( OverlappedActor );
	if (Player)
	{
		UHealthComp* HealthComp = Cast<UHealthComp>( Player->GetComponentByClass( UHealthComp::StaticClass() ) );
		if (HealthComp && HealthComp->IsInjured( OverlappedBodyPart))
		{
			FName HitBodyPart = OverlappedBodyPart;
			HealthComp->HealBodyPart( HitBodyPart , 25.0f );
		}
	}
}





