// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/DamageTestActor.h"

#include "Components/BoxComponent.h"

// Sets default values
ADamageTestActor::ADamageTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   
    BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
    this->SetRootComponent( BoxComp );
    BoxComp->InitBoxExtent( FVector( 5.0f , 5.0f , 5.0f ) );


    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
    MeshComp->SetupAttachment( RootComponent );

    BoxComp->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
    BoxComp->SetCollisionResponseToAllChannels( ECR_Overlap );
    MeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

// Called when the game starts or when spawned
void ADamageTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

