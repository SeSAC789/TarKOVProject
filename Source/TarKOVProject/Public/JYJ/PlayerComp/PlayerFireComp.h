// Fill out your copyright notice in the Description page of Project Settings.

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

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInput( UEnhancedInputComponent* input ) override;

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


	//Rifle Setting
	UPROPERTY( EditAnywhere )
	TSubclassOf<class ARifleGun> RifleGun;

	UPROPERTY()
	class ARifleGun* rifle;

	//Pistol Setting
	UPROPERTY( EditAnywhere )
	TSubclassOf<class APistolGun> PistolGun;

	UPROPERTY()
	class APistolGun* pistol;


	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bValidPistol;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bValidRifle;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bAimRifle;

	UPROPERTY( EditAnywhere )
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY( EditDefaultsOnly )
	class UParticleSystem* ExplosionVFXFactory;

	void ChoosePistol();
	void ChooseRifle();

	void SpawnPistol( TSubclassOf<APistolGun> GunFactory );
	void SpawnRifle( TSubclassOf<ARifleGun> rifleFactory );

	void Zoom();
	void ZoomIn();
	void ZoomOut();

	void Fire();
	void SetAiming(FHitResult OutHit, FVector Start, FVector EndPoint);

	UPROPERTY( EditAnywhere , BlueprintReadOnly )
	EWeaponAim aim;

private:
	void SelectedRifle();
	void SelectedPistol();
	void SelectedMachineGun();

	void FireRifle();
	void FirePistol();

};
