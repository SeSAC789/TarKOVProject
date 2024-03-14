// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/Weapon/GunBase.h"
#include "PistolGun.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API APistolGun : public AGunBase
{
	GENERATED_BODY()

public:
	APistolGun();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* pistolMesh;

public:

	UPROPERTY( Replicated )
	int32 currentAmmo;

	void UpdateAmmoCnt(int32 currentAmmo);

	/*
	UFUNCTION(Server, Reliable)
	void ServerSetAmmoCnt(int32 newAmmoCnt);

	UFUNCTION( NetMulticast , Reliable )
	void MultiSetAmmoCnt( int32 newAmmoCnt );
	*/
};
