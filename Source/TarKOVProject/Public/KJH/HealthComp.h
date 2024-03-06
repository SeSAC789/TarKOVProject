// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TARKOVPROJECT_API UHealthComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void TakeDamage( const FName& BodyPart , int32 DamageAmount, const FString& HitObjectName );

protected:
	// 각 신체 부위별 현재 HP
	UPROPERTY( VisibleAnywhere , Category = "Health" )
	TMap<FName , int32> BodyPartHP;

	// 각 신체 부위별 Max HP
	UPROPERTY( EditDefaultsOnly , Category = "Health" )
	TMap<FName , int32> BodyPartMaxHP;

	// 캐릭터의 사망 상태
	UPROPERTY( EditDefaultsOnly , Category = "Health" )
	bool bIsDead;

};
