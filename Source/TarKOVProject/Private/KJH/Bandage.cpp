// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/Bandage.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "KJH/StatusEffectComp.h"

ABandage::ABandage()
{
  
    PrimaryActorTick.bCanEverTick = false;

    BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
    this->SetRootComponent( BoxComp );
    BoxComp->InitBoxExtent( FVector( 30.0f , 30.0f , 30.0f ) );

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
    MeshComp->SetupAttachment( RootComponent );

    BoxComp->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
    BoxComp->SetCollisionResponseToAllChannels( ECR_Overlap );
    MeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );

}

void ABandage::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

    RemoveBleedingStatus( OtherActor );
}

void ABandage::RemoveBleedingStatus(AActor* OverlappedActor)
{
    if (!OverlappedActor)
    {
        return;
    }

    UStatusEffectComp* statusComp = OverlappedActor->FindComponentByClass<UStatusEffectComp>();
    if (statusComp && statusComp->IsBleeding())
    {
        // 가장 체력이 적은 부위의 출혈 상태이상을 해제
        FName WeakestBodyPart = statusComp->FindWeakestBodyPart();
        statusComp->ClearStatusEffect( EStatusEffectType::Bleeding , WeakestBodyPart );
        UE_LOG( LogTemp , Warning , TEXT( "ABandage::RemoveBleedingStatus, 출혈상태 해제: %s" ) , *WeakestBodyPart.ToString() );
    }
}

