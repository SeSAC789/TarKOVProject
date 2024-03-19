// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerComp/PlayerMoveComp.h"
#include "JYJ/PlayerBase.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KJH/StaminaComp.h"
#include "KJH/StatusEffectComp.h"


void UPlayerMoveComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime , TickType , ThisTickFunction);
}

void UPlayerMoveComp::SetupInput(UEnhancedInputComponent* input)
{
	Super::SetupInput(input);

	if (nullptr == input) return;

	// Jumping
	input->BindAction( JumpAction , ETriggerEvent::Started , this , &UPlayerMoveComp::Jump );
	//input->BindAction( JumpAction , ETriggerEvent::Completed , this , &ACharacter::StopJumping );

	// Moving
	input->BindAction( MoveAction , ETriggerEvent::Triggered , this , &UPlayerMoveComp::Move );

	// Looking
	input->BindAction( LookAction , ETriggerEvent::Triggered , this , &UPlayerMoveComp::Look );

	// Run
	input->BindAction( RunAction , ETriggerEvent::Started , this , &UPlayerMoveComp::Running );
	input->BindAction( RunAction , ETriggerEvent::Completed , this , &UPlayerMoveComp::StopRunning );

	//Crouch
	input->BindAction( CrouchAction , ETriggerEvent::Started , this , &UPlayerMoveComp::Crouch );

	//Prone
	input->BindAction( ProneAction , ETriggerEvent::Started , this , &UPlayerMoveComp::Prone );

	//Test
	input->BindAction( SplintTestAction , ETriggerEvent::Started , this , &UPlayerMoveComp::test );
}

void UPlayerMoveComp::Move(const FInputActionValue& Value)
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

void UPlayerMoveComp::Look(const FInputActionValue& Value)
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

void UPlayerMoveComp::Jump(const FInputActionValue& Value)
{
	me->Jump();
	UE_LOG(LogTemp, Warning, TEXT("TEST1"));
	
	UStaminaComp* StaminaComp = me->FindComponentByClass<UStaminaComp>();
	if (StaminaComp)
	{
		// 점프할 때 스태미나 10 소모
		StaminaComp->ConsumeStamina( 10.0f );
	}
}

void UPlayerMoveComp::Running(const FInputActionValue& Value)
{
	if (!bIsRunning)
	{
		bIsRunning = true;
		me->GetCharacterMovement()->MaxWalkSpeed *= runningSpeed;
		UStaminaComp* staminaComp = me->FindComponentByClass<UStaminaComp>();
		if (staminaComp)
		{
			// 달리기 시작할 때 스태미나 소모
			staminaComp->ConsumeStamina( staminaComp->StaminaConsumptionRate );
		}
	}
}

void UPlayerMoveComp::StopRunning(const FInputActionValue& Value)
{
	if (bIsRunning)
	{
		bIsRunning = false;
		me->GetCharacterMovement()->MaxWalkSpeed /= runningSpeed;
	}
}

void UPlayerMoveComp::Crouch(const FInputActionValue& Value)
{
	
	if (isCrouched)
	{
		me->GetCharacterMovement()->UnCrouch();
		//isCrouched = false;
		UE_LOG( LogTemp , Warning , TEXT( "test2" ) );
	}
	else {
		me->GetCharacterMovement()->Crouch();
		//isCrouched = true;
		UE_LOG( LogTemp , Warning , TEXT( "test3" ) );
	}
	

	isCrouched = !isCrouched;
}

void UPlayerMoveComp::Prone(const FInputActionValue& Value)
{
	isProned = !isProned;
}

void UPlayerMoveComp::SetRunning(bool IsRunning)
{
	bIsRunning = IsRunning;
	
	me->GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? (me->GetCharacterMovement()->MaxWalkSpeed * runningSpeed) : (me->GetCharacterMovement()->MaxWalkSpeed / runningSpeed);
}

bool UPlayerMoveComp::IsRunning() const
{
	return bIsRunning;
}

void UPlayerMoveComp::test()
{
	UE_LOG( LogTemp , Warning , TEXT( "UPlayerMoveComp::test" ) );
	RemoveFractureStatusInven( TEXT( "LeftLeg" ) );
}

void UPlayerMoveComp::RemoveFractureStatusInven(FName OverlappedBodyPart)
{
	if (!OverlappedBodyPart.IsValid())
	{
		UE_LOG( LogTemp , Warning , TEXT( "UPlayerMoveComp::RemoveFractureStatusInven IsValid" ) );
		return;
	}
	UE_LOG( LogTemp , Warning , TEXT( "UPlayerMoveComp::RemoveFractureStatusInven %s" ),*OverlappedBodyPart.ToString() );
	UStatusEffectComp* StatusComp = Cast<UStatusEffectComp>( me->GetComponentByClass( UStatusEffectComp::StaticClass() ) );
	if (StatusComp && StatusComp->IsFractured( OverlappedBodyPart ))
	{
		StatusComp->ClearStatusEffect( EStatusEffectType::Fracture , OverlappedBodyPart );
		UE_LOG( LogTemp , Warning , TEXT( "UPlayerMoveComp::RemoveFractureStatusInven, 골절상태 해제: %s" ) , *OverlappedBodyPart.ToString() );
	}
}
