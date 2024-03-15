// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/Splint.h"

#include "Components/BoxComponent.h"
#include "KJH/HealthComp.h"
#include "KJH/StatusEffectComp.h"

ASplint::ASplint()
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

void ASplint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

    UHealthComp* healthComp = Cast<UHealthComp>( OtherActor->GetComponentByClass( UHealthComp::StaticClass() ) );
    if (healthComp)
    {
        TArray<FName> FracturedParts = healthComp->GetFracturedBodyParts();
        for (FName BodyPart : FracturedParts)
        {
            RemoveFractureStatus( OtherActor , BodyPart );
        }
    }
}

void ASplint::RemoveFractureStatus(AActor* OverlappedActor, FName OverlappedBodyPart)
{
    if (!OverlappedActor)
    {
        return;
    }

    UStatusEffectComp* StatusComp = Cast<UStatusEffectComp>( OverlappedActor->GetComponentByClass( UStatusEffectComp::StaticClass() ) );
    if (StatusComp && StatusComp->IsFractured( OverlappedBodyPart ))
    {
        StatusComp->ClearStatusEffect( EStatusEffectType::Fracture , OverlappedBodyPart );
        UE_LOG( LogTemp , Warning , TEXT( "ABandage::RemoveBleedingStatus, 골절상태 해제: %s" ) , *OverlappedBodyPart.ToString() );
    }
}

