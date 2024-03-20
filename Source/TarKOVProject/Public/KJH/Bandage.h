// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJH/HealItemBase.h"
#include "Bandage.generated.h"

/**
 *
 */
UCLASS()
class TARKOVPROJECT_API ABandage : public AHealItemBase
{
	GENERATED_BODY()

public:
	ABandage();

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	class UBoxComponent* BoxComp;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	class UStaticMeshComponent* MeshComp;

	UFUNCTION( BlueprintCallable )
	void RemoveBleedingStatus( AActor* OverlappedActor , FName OverlappedBodyPart );

	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
};
