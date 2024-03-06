// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerBase.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "JYJ/PlayerdMoveComp.h"

//DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APlayerBase

APlayerBase::APlayerBase()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize( 42.f , 96.0f );

	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationYaw = true;
	this->bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator( 0.0f , 500.0f , 0.0f ); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 450.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>( TEXT( "FollowCamera" ) );
	//FollowCamera->SetupAttachment( CameraBoom , USpringArmComponent::SocketName ); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh( TEXT( "/Script/Engine.SkeletalMesh'/Game/TarKOV/JYJ/Models/Ch08/Ch08_nonPBR.Ch08_nonPBR'" ) );
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh( tmpMesh.Object );
		GetMesh()->SetRelativeLocationAndRotation( FVector( 0 , 0 , -98 ) , FRotator( 0 , -90 , 0 ) );
		GetMesh()->SetupAttachment(RootComponent );
		GetMesh()->SetOwnerNoSee( false );

		FollowCamera->SetupAttachment( GetMesh(), TEXT("CamSocket") );
		//(X=29.088001,Y=-14.927225,Z=-27.355890)
		FollowCamera->SetRelativeLocation(FVector( 29.088001 , -14.927225 , -27.355890 ));
		//(Pitch=-9.333045,Yaw=0.415788,Roll=-92.469920)
		FollowCamera->SetRelativeRotation(FRotator( -9.333045 , 0.415788 , -92.469920 ));

		aimingCamPos = CreateDefaultSubobject<USceneComponent>( TEXT( "aimingCamPos" ) );
		DefaultCamPos = CreateDefaultSubobject<USceneComponent>( TEXT( "DefaultCamPos" ) );

		aimingCamPos->SetupAttachment(GetMesh());
		DefaultCamPos->SetupAttachment(GetMesh());

		DefaultCamPos->SetWorldLocation(FollowCamera->GetRelativeLocation());
		aimingCamPos->SetWorldLocation( FollowCamera->GetRelativeLocation() + FVector(10, 0, 30));
	}


	rifleComp = CreateDefaultSubobject<USceneComponent>( TEXT( "rifleComp" ) );
	rifleComp->SetupAttachment(GetMesh(), TEXT("RifleSocket"));
	

	moveComp = CreateDefaultSubobject<UPlayerdMoveComp>( TEXT( "moveComp" ) );
	

}

void APlayerBase::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>( Controller ))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>( PlayerController->GetLocalPlayer() ))
		{
			Subsystem->AddMappingContext( DefaultMappingContext , 0 );
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerBase::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	// Set up action bindings
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>( PlayerInputComponent);

	//SetupInputDelegate.Broadcast(input);
	//moveComp->SetupInput(input);


	/*
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>( PlayerInputComponent )) {

		// Jumping
		EnhancedInputComponent->BindAction( JumpAction , ETriggerEvent::Started , this , &ACharacter::Jump );
		EnhancedInputComponent->BindAction( JumpAction , ETriggerEvent::Completed , this , &ACharacter::StopJumping );

		// Moving
		EnhancedInputComponent->BindAction( MoveAction , ETriggerEvent::Triggered , this , &APlayerBase::Move );

		// Looking
		EnhancedInputComponent->BindAction( LookAction , ETriggerEvent::Triggered , this , &APlayerBase::Look );
	}
	else
	{
		UE_LOG( LogTemplateCharacter , Error , TEXT( "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file." ) , *GetNameSafe( this ) );
	}
	*/
}

