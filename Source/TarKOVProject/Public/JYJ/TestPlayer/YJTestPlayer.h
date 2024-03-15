// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBase.h"
#include "YJTestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API AYJTestPlayer : public APlayerBase
{
	GENERATED_BODY()

public:
	AYJTestPlayer();
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;

	virtual void PossessedBy(AController* NewController) override;

	// Throw Comp Test
	//UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components" )
	//class UPlayerThrowComp* throwComp;
	
};
