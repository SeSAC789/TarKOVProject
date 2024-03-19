// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBase.h"
#include "KJH/HealItemBase.h"
#include "Splint.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API ASplint : public AHealItemBase
{
	GENERATED_BODY()
public:

	ASplint();

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	class UBoxComponent* BoxComp;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	class UStaticMeshComponent* MeshComp;

	UFUNCTION( BlueprintCallable )
	void RemoveFractureStatus( AActor* OverlappedActor , FName OverlappedBodyPart );

	UFUNCTION( BlueprintCallable )
	void RemoveFractureStatusInven( FName OverlappedBodyPart );

	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;

	UPROPERTY()
	class APlayerBase* player;
};
