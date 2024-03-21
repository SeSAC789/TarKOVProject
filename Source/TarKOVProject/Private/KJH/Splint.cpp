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

	player = Cast<APlayerBase>( GetOwner() );
}

void ASplint::NotifyActorBeginOverlap( AActor* OtherActor )
{
	Super::NotifyActorBeginOverlap( OtherActor );

	// 한 부위만 치료되게
	UHealthComp* HealthComp = Cast<UHealthComp>( OtherActor->GetComponentByClass( UHealthComp::StaticClass() ) );
	if (HealthComp)
	{
		// 골절된 부위가 없을 때까지 반복
		FName WeakestFracturedPart = HealthComp->FindWeakestFracturedBodyPart();
		while (WeakestFracturedPart != NAME_None)
		{
			// 골절 상태 해제
			RemoveFractureStatus( OtherActor , WeakestFracturedPart );
			UE_LOG( LogTemp , Warning , TEXT( "Removed Fractured for %s" ) , *WeakestFracturedPart.ToString() );

			// 다음으로 약한 골절 부위 찾기
			WeakestFracturedPart = HealthComp->FindWeakestFracturedBodyPart();
		}
	}


	// //골절된 부위를 다 담아온다
	// TArray<FName> FracturedParts = healthComp->GetFracturedBodyParts();

	// //골절된 부위들 중에 가장 아픈부위를 찾는다
	// for (FName BodyPart : FracturedParts)
	// {
	//     //만약에 골절된 부위가 가장 아픈 부위라면
	//     //Find FracturedBodyPart with the weakest

	//     if(healthComp->FindWeakestBodyPart() == BodyPart)
	//     {
	//         //골절상태 해제
	//         RemoveFractureStatus( OtherActor , BodyPart );
	//         UE_LOG(LogTemp, Warning, TEXT("Removed Fractured for %s"), *BodyPart.ToString())
	//         break;
	//     }


	// }
	//// RemoveFractureStatus( OtherActor , healthComp->FindWeakestBodyPart() );



}



void ASplint::RemoveFractureStatus( AActor* OverlappedActor , FName OverlappedBodyPart )
{
	UE_LOG( LogTemp , Warning , TEXT( "부목사용" ) );

	if (!OverlappedActor)
	{
		return;
	}

	UStatusEffectComp* StatusComp = Cast<UStatusEffectComp>( OverlappedActor->GetComponentByClass( UStatusEffectComp::StaticClass() ) );
	if (StatusComp && StatusComp->IsFractured( OverlappedBodyPart ))
	{
		StatusComp->ClearStatusEffect( EStatusEffectType::Fracture , OverlappedBodyPart );
		UE_LOG( LogTemp , Warning , TEXT( "ASplint::RemoveFractureStatus, 골절상태 해제: %s" ) , *OverlappedBodyPart.ToString() );
	}
}

void ASplint::RemoveFractureStatusInven(FName OverlappedBodyPart)
{
	if (!OverlappedBodyPart.IsValid())
	{
		return;
	}

	UStatusEffectComp* StatusComp = Cast<UStatusEffectComp>( player->GetComponentByClass( UStatusEffectComp::StaticClass() ) );
	if (StatusComp && StatusComp->IsFractured( OverlappedBodyPart ))
	{
		StatusComp->ClearStatusEffect( EStatusEffectType::Fracture , OverlappedBodyPart );
		UE_LOG( LogTemp , Warning , TEXT( "ASplint::RemoveFractureStatusInven, 골절상태 해제: %s" ) , *OverlappedBodyPart.ToString() );
	}
}

