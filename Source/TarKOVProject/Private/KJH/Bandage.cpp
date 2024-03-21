// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/Bandage.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "JYJ/PlayerBase.h"
#include "KJH/HealthComp.h"
#include "KJH/StatusEffectComp.h"

ABandage::ABandage()
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

void ABandage::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap( OtherActor );

    UHealthComp* healthComp = Cast<UHealthComp>( OtherActor->GetComponentByClass( UHealthComp::StaticClass() ) );
    if (healthComp)
    {
        TArray<FName> BleedingParts = healthComp->GetBleedingBodyParts();
        for (FName BodyPart : BleedingParts)
        {
            RemoveBleedingStatus( OtherActor , BodyPart );
        }
    }
}

void ABandage::RemoveBleedingStatus( AActor* OverlappedActor , FName OverlappedBodyPart )
{
    UE_LOG( LogTemp , Warning , TEXT( "Bandage Use" ) );

    if (!OverlappedActor)
    {
        return;
    }

    UStatusEffectComp* StatusComp = Cast<UStatusEffectComp>( OverlappedActor->GetComponentByClass( UStatusEffectComp::StaticClass() ) );
    if (StatusComp && StatusComp->IsBleeding( OverlappedBodyPart ))
    {
        StatusComp->ClearStatusEffect( EStatusEffectType::Bleeding , OverlappedBodyPart );
        UE_LOG( LogTemp , Warning , TEXT( "ABandage::RemoveBleedingStatus, 출혈상태 해제: %s" ) , *OverlappedBodyPart.ToString() );
    }
}

