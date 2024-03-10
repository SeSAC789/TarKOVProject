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

	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* pistolMesh;

	
};
