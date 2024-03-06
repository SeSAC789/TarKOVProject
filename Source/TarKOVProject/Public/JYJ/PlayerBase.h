// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN( LogTemplateCharacter , Log , All );
DECLARE_MULTICAST_DELEGATE_OneParam( FSetupInputDelegate , class UEnhancedInputComponent* );

UCLASS( config = Game )
class APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true") )
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true") )
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputMappingContext* DefaultMappingContext;

	
	APlayerBase();


public:
	// APawn interface
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;

	// To add mapping context
	virtual void BeginPlay() override;

public:
	FSetupInputDelegate SetupInputDelegate;

	UPROPERTY( EditDefaultsOnly )
	class UPlayerdMoveComp* moveComp;

	UPROPERTY( EditDefaultsOnly )
	class USceneComponent* aimingCamPos;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* DefaultCamPos;

	UPROPERTY( EditDefaultsOnly )
	class USceneComponent* rifleComp;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

