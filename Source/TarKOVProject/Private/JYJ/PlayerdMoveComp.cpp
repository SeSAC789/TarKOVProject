// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerdMoveComp.h"

#include "EnhancedInputComponent.h"
#include "JYJ/PlayerBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerdMoveComp::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime , TickType , ThisTickFunction);
}

void UPlayerdMoveComp::SetupInput(UEnhancedInputComponent* input)
{
	if(nullptr == input) return;

	
	// Jumping
	input->BindAction( JumpAction , ETriggerEvent::Started , this , &UPlayerdMoveComp::Jump );
	//input->BindAction( JumpAction , ETriggerEvent::Completed , this , &ACharacter::StopJumping );

	// Moving
	input->BindAction( MoveAction , ETriggerEvent::Triggered , this , &UPlayerdMoveComp::Move );

	// Looking
	input->BindAction( LookAction , ETriggerEvent::Triggered , this , &UPlayerdMoveComp::Look );
}

void UPlayerdMoveComp::Move( const FInputActionValue& Value )
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (me->Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = me->Controller->GetControlRotation();
		const FRotator YawRotation( 0 , Rotation.Yaw , 0 );

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::X );

		// get right vector 
		const FVector RightDirection = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::Y );

		// add movement 
		me->AddMovementInput( ForwardDirection , MovementVector.Y );
		me->AddMovementInput( RightDirection , MovementVector.X );
	}
}

void UPlayerdMoveComp::Look( const FInputActionValue& Value )
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (me->Controller != nullptr)
	{
		// add yaw and pitch input to controller
		me->AddControllerYawInput( LookAxisVector.X );
		me->AddControllerPitchInput( LookAxisVector.Y );
	}
}

void UPlayerdMoveComp::Jump(const FInputActionValue& Value)
{
	me->Jump();
}
