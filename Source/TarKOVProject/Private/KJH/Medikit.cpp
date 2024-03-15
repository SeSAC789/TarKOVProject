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

}

void AMedikit::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
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





