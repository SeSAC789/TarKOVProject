// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBaseComp.h"
#include "PlayerThrowComp.generated.h"

class ABombBase;
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

	void InputThrow();

	void SpawnGrenade( TSubclassOf<ABombBase> BombFactory );
	void throwBomb();

	UPROPERTY( EditDefaultsOnly )
	class ABombBase* grenade;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class ABombBase> BombBase;

	

private:
	UPROPERTY( EditAnywhere )
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* BombThrowAction;

	//UPROPERTY( EditDefaultsOnly )
	//class ABombBase* grenade;

	//UPROPERTY( EditAnywhere )
	//TSubclassOf<class ABombBase> GrenadeBomb;

};
