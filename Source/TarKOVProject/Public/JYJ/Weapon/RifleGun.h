// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/Weapon/GunBase.h"
#include "RifleGun.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API ARifleGun : public AGunBase
{
	GENERATED_BODY()

protected:
	ARifleGun();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	
public:

	UPROPERTY( Replicated )
	int32 currentAmmo;
	
	
};
