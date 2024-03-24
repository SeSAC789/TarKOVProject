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
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	//-----------------Input-----------------//
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* BombThrowAction;

	//-----------------Function--------------//
public:
	void InputThrow();
	void SpawnGrenade( TSubclassOf<ABombBase> BombFactory );
	void throwBomb();

	//-----------------Member variable-----------------//
public:
	UPROPERTY( Replicated, EditDefaultsOnly )
	class ABombBase* grenade;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class ABombBase> BombBase;

	UPROPERTY( EditAnywhere )
	class UPlayerAnimInstance* PlayerAnim;

	//-----------------NetWork---------------//
public:
	// client to server.
	UFUNCTION( Server , Reliable )
	void ServerRPCThrowBomb( );

	// server to multi.
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCThrowBomb();

	UFUNCTION( Server , Reliable )
	void ServerRPCTSpawnBomb( TSubclassOf<ABombBase> BombFactory );

	// server to multi.
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCSpawnBomb( TSubclassOf<ABombBase> BombFactory );

};
