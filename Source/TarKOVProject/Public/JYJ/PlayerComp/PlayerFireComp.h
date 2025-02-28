﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBaseComp.h"
#include "PlayerFireComp.generated.h"

UENUM( BlueprintType )
enum class EWeaponAim : uint8
{
	RIFLE ,
	PISTOL ,
	MACHINEGUN ,
};

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UPlayerFireComp : public UPlayerBaseComp
{
	GENERATED_BODY()

private:
	UPlayerFireComp();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInput( UEnhancedInputComponent* input ) override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	//Fire Input
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* PistolAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* RifleAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* ZoomAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* FireAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* ReloadAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* RepeatingAction;


private:
	UFUNCTION()
	void OnRep_Rifle();

	UFUNCTION()
	void OnRep_Pistol();


public:
	// ---------Call function in Player class.
	void SpawnPistol( TSubclassOf<APistolGun> GunFactory );
	void SpawnRifle( TSubclassOf<ARifleGun> rifleFactory );

	UPROPERTY( ReplicatedUsing = OnRep_Rifle , EditDefaultsOnly )
	class ARifleGun* rifle;

	UPROPERTY( ReplicatedUsing = OnRep_Pistol , EditDefaultsOnly )
	class APistolGun* pistol;

	//Rifle Setting
	UPROPERTY( EditAnywhere )
	TSubclassOf<class ARifleGun> RifleGun;

	//Pistol Setting
	UPROPERTY( EditAnywhere )
	TSubclassOf<class APistolGun> PistolGun;
	// ---------Call function in Player class.


	UPROPERTY( Replicated, EditAnywhere , BlueprintReadWrite )
	bool bValidRifle = false;

	UPROPERTY( Replicated, EditAnywhere , BlueprintReadWrite )
	bool bValidPistol = false;

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite )
	bool bAimRifle;

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadOnly )
	FVector AimStartPoint;

	UPROPERTY( Replicated, EditAnywhere , BlueprintReadOnly )
	FVector AimEndPoint;

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	EWeaponAim aim;

private:
	UPROPERTY( EditDefaultsOnly )
	class USoundBase* rifleSFX;

	UPROPERTY( EditDefaultsOnly )
	class USoundBase* pistolSFX;

	UPROPERTY( EditAnywhere )
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY( EditDefaultsOnly )
	class UParticleSystem* muzzleVFX;

	UPROPERTY( EditDefaultsOnly )
	class UParticleSystem* damageVFX;

	void ChoosePistol();
	void ChooseRifle();

	void Zoom();
	void ZoomIn();
	void ZoomOut();

	void Fire();
	void SetAiming(FHitResult OutHit, FVector Start, FVector EndPoint);

	void Reload();

	void SelectedRifle();
	void SelectedPistol();
	void SelectedMachineGun();

	void FireRifle();
	void FirePistol();

	void ChangeRepeating();

	bool bEnableRepeating;
	bool bRepeated;
	bool bReload;

	//-----------------NetWork-----------------//
private:
	void PrintNetLog();

	// Selected Pistol
	UFUNCTION( Server , Reliable )
	void ServerRPCSelectedPistol( APistolGun* selectedPistol );

	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCSelectedPistol( APistolGun* selectedPistol );				

	//Selected Rifle
	UFUNCTION( Server , Reliable )
	void ServerRPCSelectedRifle( ARifleGun* selectedRifle );				

	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCSelectedRifle( ARifleGun* selectedRifle );

	//Fire
	UFUNCTION( Server , Reliable )
	void ServerRPCFirePistol( );											

	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCFirePistol( FHitResult OutHits );


	UFUNCTION( Server , Reliable )
	void ServerRPCFireRifle();

	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCFireRifle( FHitResult OutHits );

	//Reload
	UFUNCTION( Server , Reliable )
	void ServerRPCReload();											

	//VFX
	UFUNCTION( Server , Reliable )
	void ServerFireVFX( FHitResult OutHit );

	UFUNCTION( NetMulticast , Reliable )
	void MultiFireVFX( FHitResult OutHits );

	UPROPERTY(EditDefaultsOnly)
	class APlayerBase* tempPlayer;
};
