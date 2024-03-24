// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerComp/PlayerMoveComp.h"

#include "AudioDevice.h"
#include "JYJ/PlayerBase.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KJH/StaminaComp.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"


UPlayerMoveComp::UPlayerMoveComp()
{
	SetIsReplicatedByDefault( true );
	
}

void UPlayerMoveComp::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );

	UStaminaComp* staminaComp = me->FindComponentByClass<UStaminaComp>();
	if (staminaComp)
	{
		// 달리기 상태이고, 스태미나가 남아있다면 스태미나 감소
		if (bIsRunning && staminaComp->Stamina > 0)
		{
			RunningStaminaDrain( DeltaTime );
		}
		// 달리기를 하지 않고 스태미나가 최대아니라면 스태미나 회복
		else if (!bIsRunning && staminaComp->Stamina < staminaComp->MaxStamina)
		{
			staminaComp->RecoverStamina( DeltaTime );
		}
	}
}

void UPlayerMoveComp::SetupInput( UEnhancedInputComponent* input )
{
	Super::SetupInput( input );

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
}

void UPlayerMoveComp::Move( const FInputActionValue& Value )
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

void UPlayerMoveComp::Look( const FInputActionValue& Value )
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

void UPlayerMoveComp::Jump( const FInputActionValue& Value )
{
	me->Jump();
	UE_LOG( LogTemp , Warning , TEXT( "TEST1" ) );

	UStaminaComp* StaminaComp = me->FindComponentByClass<UStaminaComp>();
	if (StaminaComp)
	{
		// 점프할 때 스태미나 10 소모
		StaminaComp->ConsumeStamina( 10.0f );
	}
}

void UPlayerMoveComp::Running( const FInputActionValue& Value )
{
	Server_Running();
}

void UPlayerMoveComp::StopRunning( const FInputActionValue& Value )
{
	Server_StopRunning();
}

void UPlayerMoveComp::Crouch( const FInputActionValue& Value )
{
	Server_Crouch();

	//강제로 서버한테 
	//OnRep_Crouch();
}

void UPlayerMoveComp::Prone( const FInputActionValue& Value )
{
	Server_Prone();
}

void UPlayerMoveComp::SetRunning( bool IsRunning )
{
	bIsRunning = IsRunning;

	me->GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? (me->GetCharacterMovement()->MaxWalkSpeed * runningSpeed) : (me->GetCharacterMovement()->MaxWalkSpeed / runningSpeed);
}

bool UPlayerMoveComp::IsRunning() const
{
	return bIsRunning;
}

/*------------Network Connection--------------*/
void UPlayerMoveComp::OnRep_Crouch()
{
	if (isCrouched)
	{
		me->GetCharacterMovement()->UnCrouch();
		//isCrouched = false;
	}
	else {
		me->GetCharacterMovement()->Crouch();
		//isCrouched = true;
	}

}

void UPlayerMoveComp::Server_Crouch_Implementation()
{
	isCrouched = !isCrouched;
	OnRep_Crouch();
}

void UPlayerMoveComp::Server_Prone_Implementation()
{
	isProned = !isProned;
}

void UPlayerMoveComp::OnReq_Running()
{
	if (!bIsRunning)
	{
		bIsRunning = true;
		me->GetCharacterMovement()->MaxWalkSpeed *= runningSpeed;
	}
	else
	{
		bIsRunning = false;
		me->GetCharacterMovement()->MaxWalkSpeed /= runningSpeed;
	}
}

void UPlayerMoveComp::Server_StopRunning_Implementation()
{
	OnReq_Running();
}

void UPlayerMoveComp::Server_Running_Implementation()
{
	Multicast_Running();
}

void UPlayerMoveComp::Multicast_Running_Implementation()
{
	OnReq_Running();
}

void UPlayerMoveComp::RunningStaminaDrain( float DeltaTime )
{
	static float RunningTime = 0.0f; // 달리기 시간 누적
	RunningTime += DeltaTime;

	// 매 1초마다 스태미나 감소
	if (RunningTime >= 1.0f)
	{
		UStaminaComp* staminaComp = me->FindComponentByClass<UStaminaComp>();
		if (staminaComp)
		{
			staminaComp->ConsumeStamina( 3.0f ); // 1초에 스태미나 1 소모
			RunningTime = 0.0f;
		}
	}
}

void UPlayerMoveComp::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UPlayerMoveComp , isCrouched );
	DOREPLIFETIME( UPlayerMoveComp , isProned );
	DOREPLIFETIME( UPlayerMoveComp , runningSpeed );
	DOREPLIFETIME( UPlayerMoveComp , bIsRunning );

}
