// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBaseComp.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "PlayerdMoveComp.generated.h"


/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UPlayerdMoveComp : public UPlayerBaseComp
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupInput(UEnhancedInputComponent* input) override;

	/** Jump Input Action */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* LookAction;



protected:

	/** Called for movement input */
	void Move( const FInputActionValue& Value );

	/** Called for looking input */
	void Look( const FInputActionValue& Value );

	/** Called for looking input */
	void Jump( const FInputActionValue& Value );

};
