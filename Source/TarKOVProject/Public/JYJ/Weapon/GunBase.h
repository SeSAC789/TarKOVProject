// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS()
class TARKOVPROJECT_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY( EditDefaultsOnly )
	class USkeletalMeshComponent* GunMeshComp;

public:
	UPROPERTY( EditDefaultsOnly )
	class USceneComponent* AimCamSocket;

	float gunAmmo;
	float gunCP ;


};
