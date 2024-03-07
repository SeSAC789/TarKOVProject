// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBaseComp.h"
#include "PlayerFireComp.generated.h"

enum  class EGunType  : uint8
{
	RIFLE,
	PISTOL,
	MACHINEGUN,
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

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* PistolAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* RifleAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* ZoomAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* FireAction;

	UPROPERTY( EditAnywhere )
	TSubclassOf<class ARifleActor> rifle;

	UPROPERTY()
	class ARifleActor* weapon;

	UPROPERTY( EditAnywhere )
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bValidRifle;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bAimRifle;

	UPROPERTY( EditDefaultsOnly )
	class UParticleSystem* ExplosionVFXFactory;

	UPROPERTY( EditDefaultsOnly )
	class UStaticMeshComponent* TraceGun;

	UPROPERTY( EditAnywhere )
	TSubclassOf<class ADamageTestActor> DamageActorFactory;


	float targetFOV = 90 ;

	void ChoosePistol();
	void ChooseRifle();

	void AttachPistol();
	void AttachRifle( TSubclassOf<ARifleActor> rifleFactory );

	void Zoom();
	void ZoomIn();
	void ZoomOut();

	void Fire();

};
