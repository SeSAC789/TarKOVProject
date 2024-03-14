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
	


public:

	UFUNCTION()
	void OnRep_Rifle();

	UFUNCTION()
	void OnRep_Pistol();

	UPROPERTY( ReplicatedUsing = OnRep_Rifle , EditDefaultsOnly )
	class ARifleGun* rifle;

	UPROPERTY( ReplicatedUsing = OnRep_Pistol , EditDefaultsOnly )
	class APistolGun* pistol;

	UPROPERTY( Replicated, EditAnywhere , BlueprintReadWrite )
	bool bValidRifle = false;

	UPROPERTY( Replicated, EditAnywhere , BlueprintReadWrite )
	bool bValidPistol = false;



	//Rifle Setting
	UPROPERTY( EditAnywhere )
	TSubclassOf<class ARifleGun> RifleGun;

	//Pistol Setting
	UPROPERTY( EditAnywhere )
	TSubclassOf<class APistolGun> PistolGun;

	



	UPROPERTY( Replicated, EditAnywhere , BlueprintReadWrite )
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

	void Reload();

private:
	void SelectedRifle();
	void SelectedPistol();
	void SelectedMachineGun();

	void FireRifle();
	void FirePistol();

	void ChangeRepeating();

	bool bEnableRepeating;
	bool bRepeated;


	//-----------------NetWork-----------------//
public:
	// client to server. 손에 붙여 주세요. (총 액터의 포인터)
	UFUNCTION( Server , Reliable )
	void ServerRPCSpawnPistol( TSubclassOf<APistolGun> GunFactory );				

	// server to multi. 손에 붙이세요. (총 액터의 포인터)
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCSpawnPistol( APistolGun* OwnPistol );				

	//SelectedPistol
	// client to server.
	UFUNCTION( Server , Reliable )
	void ServerRPCSelectedPistol( APistolGun* selectedPistol );				

	// server to multi.
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCSelectedPistol( APistolGun* selectedPistol );				

	// client to server. 손에 붙여 주세요. (총 액터의 포인터)
	UFUNCTION( Server , Reliable )
	void ServerRPCSpawnRifle( TSubclassOf<ARifleGun> GunFactory );				

	// server to multi. 손에 붙이세요. (총 액터의 포인터)
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCSpawnRifle( ARifleGun* OwnRifle );				

	//SelectedPistol
	// client to server.
	UFUNCTION( Server , Reliable )
	void ServerRPCSelectedRifle( ARifleGun* selectedPistol );				

	// server to multi.
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCSelectedRifle( ARifleGun* selectedPistol );				

	//Fire
	// client to server.
	UFUNCTION( Server , Reliable )
	void ServerRPCFirePistol( );											

	// server to multi.
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCFirePistol( bool bHit, const FHitResult& hitInfo );		

	// client to server.
	UFUNCTION( Server , Reliable )
	void ServerRPCFireRifle();

	// server to multi.
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCFireRifle( bool bHit , const FHitResult& hitInfo );


	//Reload
	// client to server.
	UFUNCTION( Server , Reliable )
	void ServerRPCReload();											

	// server to multi.
	UFUNCTION( NetMulticast , Reliable )
	void MultiRPCReload( );		



};
