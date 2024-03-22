// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBaseComp.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "PlayerMoveComp.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UPlayerMoveComp : public UPlayerBaseComp
{
	GENERATED_BODY()

public:
	UPlayerMoveComp();
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;
	virtual void SetupInput( UEnhancedInputComponent* input ) override;
	void RunningStaminaDrain(float DeltaTime);
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Jump Input Action */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* LookAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* RunAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* CrouchAction;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* ProneAction;

	/** Called for movement input */
	void Move( const FInputActionValue& Value );

	/** Called for looking input */
	void Look( const FInputActionValue& Value );

	/** Called for looking input */
	void Jump( const FInputActionValue& Value );

	void Running( const FInputActionValue& Value );
	void StopRunning( const FInputActionValue& Value );
	void Crouch( const FInputActionValue& Value );
	void Prone( const FInputActionValue& Value );

public:
	UPROPERTY(Replicated, EditDefaultsOnly)
	float runningSpeed = 2.0f;

	UPROPERTY( ReplicatedUsing = OnRep_Crouch, EditAnywhere , BlueprintReadWrite )
	bool isCrouched;

	UPROPERTY( Replicated , EditAnywhere , BlueprintReadWrite)
	bool isProned;

public:
	UPROPERTY( ReplicatedUsing = OnReq_Running , EditAnywhere , BlueprintReadWrite )
	bool bIsRunning;

	// 달리기 상태를 설정하고 가져오는 함수
	void SetRunning( bool IsRunning );
	bool IsRunning() const;

	/*------------Network Connection--------------*/
	// Courch
	UFUNCTION()
	void OnRep_Crouch();

	UFUNCTION( Server , UnReliable )
	void Server_Crouch();

	UFUNCTION( Server , UnReliable )
	void Server_Prone();

	//Running
	UFUNCTION()
	void OnReq_Running();

	UFUNCTION( Server , UnReliable )
	void Server_Running();

	UFUNCTION( NetMulticast , UnReliable )
	void Multicast_Running();

	UFUNCTION( Server , UnReliable )
	void Server_StopRunning();

};
