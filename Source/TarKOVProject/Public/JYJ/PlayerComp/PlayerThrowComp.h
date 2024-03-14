// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBaseComp.h"
#include "PlayerThrowComp.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UPlayerThrowComp : public UPlayerBaseComp
{
	GENERATED_BODY()

public:
	UPlayerThrowComp();

	virtual void BeginPlay() override;
	virtual void SetupInput( UEnhancedInputComponent* input ) override;

	//void SpawnGrenade( TSubclassOf<ABombBase> BombFactory );

private:
	UPROPERTY( EditAnywhere )
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* BombThrowAction;

	void throwBomb();

	//UPROPERTY( EditDefaultsOnly )
	//class ABombBase* grenade;

	//UPROPERTY( EditAnywhere )
	//TSubclassOf<class ABombBase> GrenadeBomb;

};
