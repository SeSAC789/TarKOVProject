﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerBase.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "JYJ/PlayerComp/PlayerFireComp.h"
#include "JYJ/PlayerComp/PlayerMoveComp.h"
#include "KJH/HealthComp.h"
#include "KJH/HPWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/PostProcessComponent.h"
#include "JYJ/Controller/TarKOVPlayerController.h"
#include "JYJ/PlayerComp/PlayerThrowComp.h"
#include "JYJ/Trigger/TriggerEscapeLocation.h"
#include "JYJ/Weapon/BombBase.h"
#include "KJH/Bandage.h"
#include "KJH/Medikit.h"
#include "KJH/Splint.h"
#include "KJH/StaminaComp.h"
#include "JYJ/GameOverWidget.h"

//DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APlayerBase

APlayerBase::APlayerBase()
{
	// collision capsule Settings
	GetCapsuleComponent()->InitCapsuleSize( 42.f , 96.0f );

	// Player Controller Rotation Settings
	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationYaw = true;
	this->bUseControllerRotationRoll = false;

	// Player movement Settings
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator( 0.0f , 500.0f , 0.0f ); 
	
	GetCharacterMovement()->JumpZVelocity = 450.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	//Crouch Speed Setting
	GetCharacterMovement()->MaxWalkSpeedCrouched = 180.0f;

	// Player Cam Settings
	FollowCamera = CreateDefaultSubobject<UCameraComponent>( TEXT( "FollowCamera" ) );
	FollowCamera->bUsePawnControlRotation = true; 

	// PlayerMesh Settings
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh( TEXT( "/Script/Engine.SkeletalMesh'/Game/TarKOV/JYJ/Models/Ch08/Ch08_nonPBR.Ch08_nonPBR'" ) );
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh( tmpMesh.Object );
		GetMesh()->SetRelativeLocationAndRotation( FVector( 0 , 0 , -98 ) , FRotator( 0 , -90 , 0 ) );
		GetMesh()->SetupAttachment(RootComponent );
		GetMesh()->SetOwnerNoSee( false );

		FollowCamera->SetupAttachment( GetMesh(), TEXT("CamSocket") );
		FollowCamera->SetRelativeLocation(FVector( 0 , -14.927225 , -27.355890 ));
		FollowCamera->SetRelativeRotation(FRotator( -9.333045 , 0.415788 , -92.469920 ));

		PainPostProcessComp = CreateDefaultSubobject<UPostProcessComponent>( TEXT( "PainPostProcessComp" ) );
		PainPostProcessComp->SetupAttachment( FollowCamera );

		//사용하는지 확인 필요
		aimingCamPos = CreateDefaultSubobject<USceneComponent>( TEXT( "aimingCamPos" ) );
		DefaultCamPos = CreateDefaultSubobject<USceneComponent>( TEXT( "DefaultCamPos" ) );

		aimingCamPos->SetupAttachment(GetMesh());
		DefaultCamPos->SetupAttachment(GetMesh() , TEXT( "CamSocket" ) );

		DefaultCamPos->SetRelativeLocationAndRotation(FollowCamera->GetRelativeLocation(), FollowCamera->GetRelativeRotation());
		aimingCamPos->SetWorldLocation( FollowCamera->GetRelativeLocation() + FVector(10, 0, 30));
	}

	// Rifle Hand Socket Settings
	rifleComp = CreateDefaultSubobject<USceneComponent>( TEXT( "rifleComp" ) );
	rifleComp->SetupAttachment(GetMesh(), TEXT("RifleSocket1"));
	//rifleComp->SetRelativeRotation(FRotator(0, 0, -10));

	// Pistol Hand Socket Settings
	pistolComp = CreateDefaultSubobject<USceneComponent>( TEXT( "pistolComp" ) );
	pistolComp->SetupAttachment( GetMesh() , TEXT( "PistolSocket" ) );
	//pistolComp->SetRelativeRotation( FRotator( 0 , 0 , -10 ) );

	//부위 별 데미지 Setting Function
	SetPartitionDamageCollision();


	//Player기능 Actor Component 정의
	moveComp = CreateDefaultSubobject<UPlayerMoveComp>( TEXT( "moveComp" ) );
	HealthComp = CreateDefaultSubobject<UHealthComp>( TEXT( "HealthComp" ) );
	fireComp = CreateDefaultSubobject<UPlayerFireComp>( TEXT( "fireComp" ) );
	statusComp = CreateDefaultSubobject<UStatusEffectComp>( TEXT( "statusComp" ) );
	staminaComp = CreateDefaultSubobject<UStaminaComp>( TEXT( "staminaComp" ) );
	throwComp = CreateDefaultSubobject<UPlayerThrowComp>( TEXT( "throwComp" ) );
	
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();

	HeadHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	ThoraxHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	StomachHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	RightArmUpperHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	RightForeArmHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	LeftArmUpperHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	LeftForeArmHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	RightLegUpperHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	RightLegLowerHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	LeftLegUpperHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );
	LeftLegLowerHitbox->OnComponentBeginOverlap.AddDynamic( this , &APlayerBase::OnHitboxOverlap );

	InitUI();

	//네트워크 업데이트 빈도
	NetUpdateFrequency = 100;


	// Player Controller Input Settings
	if (APlayerController* PlayerController = Cast<APlayerController>( Controller ))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>( PlayerController->GetLocalPlayer() ))
		{
			Subsystem->AddMappingContext( DefaultMappingContext , 0 );
		}
	}
}

void APlayerBase::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	UEnhancedInputComponent* input = CastChecked<UEnhancedInputComponent>( PlayerInputComponent);

	//자식 class 에서 호출 
	SetupInputDelegate.Broadcast(input);
	
}

void APlayerBase::OnHitboxOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
	UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	if (this == OtherActor || Cast<ABandage>( OtherActor ) || Cast<ASplint>(OtherActor) || Cast<AMedikit>( OtherActor ) || Cast<ATriggerEscapeLocation>( OtherActor )
		|| Cast<ABombBase>( OtherActor ))
	{
		return;
	}

	if (OverlappedComponent->ComponentHasTag( "Head" ) || OverlappedComponent->ComponentHasTag( "Thorax" ) || OverlappedComponent->ComponentHasTag( "Stomach" ) || OverlappedComponent->ComponentHasTag( "RightArm" ) || OverlappedComponent->ComponentHasTag( "LeftArm" ) || OverlappedComponent->ComponentHasTag( "RightLeg" ) || OverlappedComponent->ComponentHasTag( "LeftLeg" ))
	{
		FName BodyPart = OverlappedComponent->ComponentTags[0]; // 첫 번째 태그를 신체 부위 이름으로 사용
		if (HealthComp)
		{
			FString HitObjectName = OtherActor->GetName(); // 충돌한 객체의 이름
			HealthComp->TakeDamage( BodyPart , 5 , HitObjectName ); // 모든 충돌에 대해 5의 데미지를 적용, 충돌한 객체 이름을 전달
		}
	}
}

void APlayerBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy( NewController );


	// player main UI 호출
	InitUI();

	// player gun spawn
	if (APlayerBase* NewCharacter = Cast<APlayerBase>( NewController->GetCharacter() ))
	{
		if (!NewCharacter->fireComp && !NewCharacter->throwComp)
		{
			UE_LOG( LogTemp , Warning , TEXT( "APlayerGameMode::OnPostLogin - No FireComp" ) )
				return;
		}

		NewCharacter->fireComp->SpawnRifle( NewCharacter->fireComp->RifleGun );
		NewCharacter->fireComp->SpawnPistol( NewCharacter->fireComp->PistolGun );

		//NewCharacter->throwComp->SpawnGrenade( NewCharacter->throwComp->BombBase );
	}
	else
	{
		UE_LOG( LogTemp , Warning , TEXT( "APlayerGameMode::OnPostLogin - No Character" ) )
	}
}

void APlayerBase::SetPartitionDamageCollision()
{
	/*부위 별 데미지 충돌체*/
	HeadHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "HeadHitbox" ) );
	HeadHitbox->SetupAttachment( GetMesh() , FName( "HeadSocket" ) );
	HeadHitbox->SetCapsuleSize( 11.0f , 12.0f ); // 캡슐의 크기 설정 (반지름, 높이)
	HeadHitbox->SetRelativeLocationAndRotation( FVector( 0.0f , -8.281382f , 4.830602f ) , FRotator( 0.0f , 0.0f , 90.0f ) );
	// 소켓에 대한 상대 위치 설정 (X=0.000000,Y=-8.281382,Z=4.830602), (Pitch=0.000000,Yaw=0.000000,Roll=-90.000000)
	// "Head" 태그 추가
	HeadHitbox->ComponentTags.Add( FName( "Head" ) );

	ThoraxHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "ThoraxHitbox" ) );
	ThoraxHitbox->SetupAttachment( GetMesh() , FName( "ThoraxSocket" ) );
	ThoraxHitbox->SetCapsuleSize( 16.0f , 17.0f );
	ThoraxHitbox->SetRelativeLocationAndRotation( FVector( 0.5f , 1.560810f , 4.163126f ) , FRotator( 0.0f , 0.0f , 90.0f ) );
	// (X=0.500000,Y=1.560810,Z=4.163126) (Pitch=0.000000,Yaw=0.000000,Roll=90.000000) 
	// "Thorax" 태그 추가
	ThoraxHitbox->ComponentTags.Add( FName( "Thorax" ) );

	StomachHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "StomachHitbox" ) );
	StomachHitbox->SetupAttachment( GetMesh() , FName( "StomachSocket" ) );
	StomachHitbox->SetCapsuleSize( 15.0f , 15.0f );
	StomachHitbox->SetRelativeLocationAndRotation( FVector( 0.5f , 0.640273f , 5.005143f ) , FRotator( 0.0f , 0.0f , 0.0f ) );
	// (X=0.500000,Y=0.640273,Z=5.005143) 
	// "Stomach" 태그 추가
	StomachHitbox->ComponentTags.Add( FName( "Stomach" ) );

	RightArmUpperHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightArmUpperHitbox" ) );
	RightArmUpperHitbox->SetupAttachment( GetMesh() , FName( "RightArmUpperSocket" ) );
	RightArmUpperHitbox->SetCapsuleSize( 6.5f , 20.0f );
	RightArmUpperHitbox->SetRelativeLocationAndRotation( FVector( 0.023172f , -12.472641f , -0.557689f ) , FRotator( 2.22837f , 4.517647f , 91.695983f ) );
	// (X=0.023172,Y=-12.472641,Z=-0.557689) (Pitch=2.228372,Yaw=4.517647,Roll=91.695983)
	// "RightArm" 태그 추가
	RightArmUpperHitbox->ComponentTags.Add( FName( "RightArm" ) );

	RightForeArmHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightForeArmHitbox" ) );
	RightForeArmHitbox->SetupAttachment( GetMesh() , FName( "RightForeArmSocket" ) );
	RightForeArmHitbox->SetCapsuleSize( 6.0f , 20.0f );
	RightForeArmHitbox->SetRelativeLocationAndRotation( FVector( 0.458593f , -21.358836f , -0.090714f ) , FRotator( 2.275739f , 7.835439f , 86.318466f ) );
	// (X=0.458593,Y=-21.358836,Z=-0.090714) (Pitch=2.275739,Yaw=7.835439,Roll=86.318466)
	// "RightArm" 태그 추가
	RightForeArmHitbox->ComponentTags.Add( FName( "RightArm" ) );

	LeftArmUpperHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftArmUpperHitbox" ) );
	LeftArmUpperHitbox->SetupAttachment( GetMesh() , FName( "LeftArmUpperSocket" ) );
	LeftArmUpperHitbox->SetCapsuleSize( 6.5f , 20.0f );
	LeftArmUpperHitbox->SetRelativeLocationAndRotation( FVector( -0.656969f , -12.241082f , -0.199606f ) , FRotator( 9.024780f , -4.985366f , 92.502085f ) );
	// (X=-0.656969,Y=-12.241082,Z=-0.199606) (Pitch=9.024780,Yaw=-4.985366,Roll=92.502085)
	// "LeftArm" 태그 추가
	LeftArmUpperHitbox->ComponentTags.Add( FName( "LeftArm" ) );

	LeftForeArmHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftForeArmHitbox" ) );
	LeftForeArmHitbox->SetupAttachment( GetMesh() , FName( "LeftForeArmSocket" ) );
	LeftForeArmHitbox->SetCapsuleSize( 6.0f , 20.0f );
	LeftForeArmHitbox->SetRelativeLocationAndRotation( FVector( 0.253245f , -21.7371221f , 0.386370f ) , FRotator( -1.546471f , -6.300808f , 87.828338f ) );
	// (X=0.253245,Y=-21.737122,Z=0.386370) (Pitch=-1.546471,Yaw=-6.300808,Roll=87.828338)
	// "LeftArm" 태그 추가
	LeftForeArmHitbox->ComponentTags.Add( FName( "LeftArm" ) );

	RightLegUpperHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightLegUpperHitbox" ) );
	RightLegUpperHitbox->SetupAttachment( GetMesh() , FName( "RightLegUpperSocket" ) );
	RightLegUpperHitbox->SetCapsuleSize( 11.0f , 27.0f );
	RightLegUpperHitbox->SetRelativeLocationAndRotation( FVector( -0.406686f , -18.666032f , 1.906051f ) , FRotator( -0.233612f , 0.556462f , 90.846342f ) );
	// (X=-0.406686,Y=-18.666032,Z=1.906051) (Pitch=-0.233612,Yaw=0.556462,Roll=90.846342)
	// "RightLeg" 태그 추가
	RightLegUpperHitbox->ComponentTags.Add( FName( "RightLeg" ) );

	RightLegLowerHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightLegLowerHitbox" ) );
	RightLegLowerHitbox->SetupAttachment( GetMesh() , FName( "RightLegLowerSocket" ) );
	RightLegLowerHitbox->SetCapsuleSize( 9.0f , 25.0f );
	RightLegLowerHitbox->SetRelativeLocationAndRotation( FVector( -0.374272f , -20.185090f , -0.795077f ) , FRotator( 0.786182f , -4.247138f , 90.992866f ) );
	// (X=-0.374272,Y=-20.185090,Z=-0.795077) (Pitch=0.786182,Yaw=-4.247138,Roll=90.992866)
	// "RightLeg" 태그 추가
	RightLegLowerHitbox->ComponentTags.Add( FName( "RightLeg" ) );

	LeftLegUpperHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftLegUpperHitbox" ) );
	LeftLegUpperHitbox->SetupAttachment( GetMesh() , FName( "LeftLegUpperSocket" ) );
	LeftLegUpperHitbox->SetCapsuleSize( 11.0f , 27.0f );
	LeftLegUpperHitbox->SetRelativeLocationAndRotation( FVector( 0.788391f , -18.530999f , 0.717755f ) , FRotator( 0.168281f , -2.991637f , 87.833028f ) );
	// (X=0.788391,Y=-18.530999,Z=0.717755) (Pitch=0.168281,Yaw=-2.991637,Roll=87.833028)
	// "LeftLeg" 태그 추가
	LeftLegUpperHitbox->ComponentTags.Add( FName( "LeftLeg" ) );

	LeftLegLowerHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftLegLowerHitbox" ) );
	LeftLegLowerHitbox->SetupAttachment( GetMesh() , FName( "LeftLegLowerSocket" ) );
	LeftLegLowerHitbox->SetCapsuleSize( 9.0f , 25.0f );
	LeftLegLowerHitbox->SetRelativeLocationAndRotation( FVector( -0.343941f , -20.073776f , -0.984876f ) , FRotator( -2.179116f , -0.535826f , 89.314173f ) );
	// (X=-0.343941,Y=-20.073776,Z=-0.984876) (Pitch=-2.179116,Yaw=-0.535826,Roll=89.314173)
	// "LeftLeg" 태그 추가
	LeftLegLowerHitbox->ComponentTags.Add( FName( "LeftLeg" ) );
}

void APlayerBase::InitUI()
{
	// 컨트롤러가 PlayerController가 아니라면 함수를 바로 종료
	// 즉, mainUI를 생성하지 않겠다.
	auto pc = Cast<ATarKOVPlayerController>( Controller );
	if (nullptr == pc)
	{
		UE_LOG( LogTemp , Warning , TEXT( "%s : nullptr == pc" ) , __FUNCTION__ );
		return;
	}
	if (false == IsLocallyControlled())
	{
		UE_LOG( LogTemp , Warning , TEXT( "%s : false == IsLocallyControlled()" ) , __FUNCTION__ );
		return;
	}

	UE_LOG( LogTemp , Warning , TEXT( "AJHPlayerTest::InitUI" ) );


	if (nullptr == pc->PlayerMainUI)
	{
		// MainUI를 생성해서 기억하고싶다.
		pc->PlayerMainUI = CreateWidget<UHPWidget>( GetWorld() , pc->PlayerMainUIFactory );
		// AddToViewport하고싶다.
		pc->PlayerMainUI->AddToViewport();
		// 타이머 카운트 다운 시작하고싶다.
		pc->PlayerMainUI->GameStartCountdown( 300 );

		pc->PlayerMainUI->PlayEscapeAnim();
	}

	// 만들어진 mainUI를 기억하고싶다.
	PlayerMainUI = pc->PlayerMainUI;
	// 만들어진 GameOVerUI를 기억하고싶다.
	GameOverUI = pc->GameOverUI;

	PlayerMainUI = pc->PlayerMainUI;
}

void APlayerBase::DamageProcess()
{
	// 죽음 애니메이션이 끝나면
    // 마우스 커서를 보이게하고싶다.
	auto pc = Cast<ATarKOVPlayerController>( Controller );
	pc->SetShowMouseCursor( true );
	// 화면을 회색으로 보이게 하고싶다.
	FollowCamera->PostProcessSettings.ColorSaturation = FVector4( 0 , 0 , 0 , 1 );
	// 게임오버UI를 보이게하고싶다.
	if (nullptr == pc->GameOverUI)
	{
		// GameOverUI를 생성해서 기억하고싶다.
		pc->GameOverUI = CreateWidget<UGameOverWidget>( GetWorld() , pc->GameOverUIFactory );
		// AddToViewport하고싶다.
		pc->GameOverUI->AddToViewport();
	}
}

void APlayerBase::OnDeath()
{
	GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );

	// 캐릭터 움직임을 멈추고 싶다.
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
		GetCharacterMovement()->SetComponentTickEnabled( false );
	}

	// 마우스 및 카메라 회전 비활성화
	APlayerController* pc = Cast<APlayerController>( GetController() );
	if (pc)
	{
		pc->SetIgnoreLookInput( true ); // 카메라(시선) 움직임을 무시하도록 설정
		pc->SetIgnoreMoveInput( true ); // 이동 입력을 무시하도록 설정
	}
}
