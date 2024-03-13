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

    UStatusEffectComp* StatusEffectComp = OverlappedActor->FindComponentByClass<UStatusEffectComp>();
    if (StatusEffectComp)
    {
        // 가장 체력이 적은 부위의 출혈 상태이상을 해제
        FName WeakestBodyPart = StatusEffectComp->FindWeakestBodyPart();
        // 여기에 로그를 추가
        UE_LOG( LogTemp , Warning , TEXT( "Removed bleeding status from: %s" ) , *WeakestBodyPart.ToString() );
    }
}

