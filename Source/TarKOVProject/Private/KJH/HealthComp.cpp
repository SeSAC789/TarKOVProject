// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/HealthComp.h"

// Sets default values for this component's properties
UHealthComp::UHealthComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

     // 각 신체 부위별 기본 HP 값 초기화
    BodyPartMaxHealth.Add( "Head" , 35.f );
    BodyPartMaxHealth.Add( "Thorax" , 85.f );
    BodyPartMaxHealth.Add( "Stomach" , 70.f );
    BodyPartMaxHealth.Add( "RightArm" , 60.f );
    BodyPartMaxHealth.Add( "LeftArm" , 60.f );
    BodyPartMaxHealth.Add( "RightLeg" , 65.f );
    BodyPartMaxHealth.Add( "LeftLeg" , 65.f );

    // MaxHP 값을 사용하여 각 부위의 현재 건강 상태 초기화
    for (const auto& Elem : BodyPartMaxHealth)
    {
        BodyPartCurrentHealth.Add( Elem.Key , Elem.Value );
    }
}


// Called when the game starts
void UHealthComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComp::TakeDamage(const FName& BodyPart, float DamageAmount)
{
    if (BodyPartCurrentHealth.Contains( BodyPart ))
    {
        // 해당 신체 부위의 건강 상태 감소
        BodyPartCurrentHealth[BodyPart] -= DamageAmount;

        // 머리 또는 흉부 부위의 체력이 0 이하인 경우 즉시 사망 처리
        if ((BodyPart == FName( "Head" ) || BodyPart == FName( "Thorax" )) && BodyPartCurrentHealth[BodyPart] <= 0.f)
        {
            // 즉시 사망 이후 관련 함수 구현하자, 죽음 애니메이션 제생, 게임오버 ui등 구현
        }
      
    }
}

