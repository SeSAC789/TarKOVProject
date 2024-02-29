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
	class UCapsuleComponent* RightArmHitbox;
	// 왼팔
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftArmHitbox;
	// 오른다리
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* RightLegHitbox;
	// 왼다리
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftLegHitbox;

};
