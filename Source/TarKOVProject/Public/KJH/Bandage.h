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

	UPROPERTY( EditAnywhere , BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	class UStaticMeshComponent* MeshComp;

	// 출혈 상태이상 해제를 위한 함수
	UFUNCTION( BlueprintCallable )
	void RemoveBleedingStatus( AActor* OverlappedActor , FName OverlappedBodyPart );

public:
	// 오버랩 시작 이벤트 처리
	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
};
