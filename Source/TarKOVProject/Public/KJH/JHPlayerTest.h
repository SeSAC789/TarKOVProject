// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBase.h"
#include "JHPlayerTest.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API AJHPlayerTest : public APlayerBase
{
	GENERATED_BODY()

	AJHPlayerTest();

	// To add mapping context
	virtual void BeginPlay() override;

public:
	// 머리
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* HeadHitbox;
	// 흉부
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* ThoraxHitbox;
	// 복부
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* StomachHitbox;
	// 오른팔
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* RightArmUpperHitbox;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* RightForeArmHitbox;
	// 왼팔
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftArmUpperHitbox;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftForeArmHitbox;
	// 오른다리
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* RightLegUpperHitbox;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* RightLegLowerHitbox;
	// 왼다리
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftLegUpperHitbox;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftLegLowerHitbox;

};
