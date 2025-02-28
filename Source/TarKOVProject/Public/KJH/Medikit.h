﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJH/HealItemBase.h"
#include "Medikit.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API AMedikit : public AHealItemBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AMedikit();

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	class UBoxComponent* BoxComp;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	class UStaticMeshComponent* MeshComp;

	UPROPERTY()
	class APlayerBase* player;

	UPROPERTY()
	class UHealthComp* healthComp;

	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;

	UFUNCTION( BlueprintCallable )
	void RecoveryHP( AActor* OverlappedActor , FName OverlappedBodyPart );



};
