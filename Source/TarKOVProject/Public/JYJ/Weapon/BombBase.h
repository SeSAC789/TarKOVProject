// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombBase.generated.h"

UCLASS()
class TARKOVPROJECT_API ABombBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABombBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	void explosiveBomb();

private:
	UPROPERTY( EditAnywhere )
	class UStaticMeshComponent* GrenadeMesh;

	UPROPERTY( EditDefaultsOnly )
	float detectRadius = 100.f;

	UPROPERTY( EditDefaultsOnly )
	class UProjectileMovementComponent* throwDir;

	UPROPERTY( EditDefaultsOnly )
	class UParticleSystem* ExplosionVFXFactory;

};
