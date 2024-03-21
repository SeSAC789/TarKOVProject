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

private:
	UPlayerThrowComp();
	virtual void BeginPlay() override;
	virtual void SetupInput( UEnhancedInputComponent* input ) override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	void InputThrow();

	

public:
	void SpawnGrenade( TSubclassOf<ABombBase> BombFactory );
	//void SpawnGrenade( ABombBase grenade );
	void throwBomb();

	UPROPERTY( Replicated, EditDefaultsOnly )
	class ABombBase* grenade;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class ABombBase> BombBase;


private:
	UPROPERTY( EditAnywhere )
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* BombThrowAction;

	UPROPERTY( EditDefaultsOnly )
	class UParticleSystem* ExplosionVFXFactory;

	//UPROPERTY( EditDefaultsOnly )
	//class ABombBase* grenade;

	//UPROPERTY( EditAnywhere )
	//TSubclassOf<class ABombBase> GrenadeBomb;

	//Reload
	// client to server.
	UFUNCTION( Server , Reliable )
	void ServerRPCThrowBomb( );

	// server to multi.
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCThrowBomb( ABombBase* selectedBomb );

};
