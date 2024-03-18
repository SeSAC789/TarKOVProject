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
        //골절된 부위를 다 담아온다
        TArray<FName> FracturedParts = healthComp->GetFracturedBodyParts();

        //골절된 부위들 중에 가장 아픈부위를 찾는다
        for (FName BodyPart : FracturedParts)
        {
            //만약에 골절된 부위가 가장 아픈 부위라면
            //Find FracturedBodyPart with the weakest



            if(healthComp->FindWeakestBodyPart() == BodyPart)
            {
                //골절상태 해제
                RemoveFractureStatus( OtherActor , BodyPart );
                UE_LOG(LogTemp, Warning, TEXT("Removed Fractured for %s"), *BodyPart.ToString())
                break;
            }


        }
       // RemoveFractureStatus( OtherActor , healthComp->FindWeakestBodyPart() );


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

