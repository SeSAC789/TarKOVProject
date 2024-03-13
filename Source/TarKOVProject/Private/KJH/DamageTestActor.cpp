// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/DamageTestActor.h"

#include "Components/BoxComponent.h"
#include "JYJ/PlayerBase.h"

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

    BoxComp->OnComponentBeginOverlap.AddDynamic( this , &ADamageTestActor::OnOverlapBegin );

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

void ADamageTestActor::OnOverlapBegin( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
    UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
    // 만약 충돌한 액터가 플레이어 베이스라면
    if (APlayerBase* PlayerBase = Cast<APlayerBase>( OtherActor ))
    {
        // 플레이어 베이스의 데미지 처리 함수 호출
        PlayerBase->OnHitboxOverlap( BoxComp , this , OtherComp , OtherBodyIndex , bFromSweep , SweepResult );
    }
}