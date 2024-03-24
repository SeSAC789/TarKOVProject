// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerComp/PlayerFireComp.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/Animation/PlayerAnimInstance.h"
#include "JYJ/Weapon/PistolGun.h"
#include "JYJ/Weapon/RifleGun.h"
#include "Kismet/GameplayStatics.h"
#include "KJH/HealthComp.h"
#include "Net/UnrealNetwork.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "Misc/OutputDeviceNull.h"

UPlayerFireComp::UPlayerFireComp()
{
	
	SetIsReplicatedByDefault( true );

	AudioComponent = CreateDefaultSubobject<UAudioComponent>( TEXT( "AudioComponent" ) );
	AudioComponent->bAutoActivate = false; 
	//AudioComponent->AutoAttachParent;
}

void UPlayerFireComp::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnim = Cast<UPlayerAnimInstance>( me->GetMesh()->GetAnimInstance() );
	check( PlayerAnim );

	// BeginPlay에서 RPC 실행 시, 타이밍 상 반복 호출될 수 있음
	// -> Possess By 함수에서 호출

	bRepeated = false;
	bAimRifle = false;
	bEnableRepeating = false;
	AudioComponent->AttachToComponent( GetOwner()->GetRootComponent() , FAttachmentTransformRules::KeepRelativeTransform );

}

void UPlayerFireComp::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );
	//Zoom();

	PrintNetLog();
	//UE_LOG(LogTemp, Warning, TEXT("Rifle Ammo %d"), me->fireComp->rifle->currentAmmo);

	/*
	if(me->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("test"));
	}
	*/

}

void UPlayerFireComp::SetupInput( UEnhancedInputComponent* input )
{
	Super::SetupInput( input );

	if (nullptr == input) return;

	//Pistol
	input->BindAction( PistolAction , ETriggerEvent::Started , this , &UPlayerFireComp::ChoosePistol );

	//Rifle
	input->BindAction( RifleAction , ETriggerEvent::Started , this , &UPlayerFireComp::ChooseRifle );

	//Zoom
	input->BindAction( ZoomAction , ETriggerEvent::Started , this , &UPlayerFireComp::ZoomIn );
	input->BindAction( ZoomAction , ETriggerEvent::Completed , this , &UPlayerFireComp::ZoomOut );

	//Fire
	input->BindAction( FireAction , ETriggerEvent::Started , this , &UPlayerFireComp::Fire );

	//Reload
	input->BindAction( ReloadAction , ETriggerEvent::Started , this , &UPlayerFireComp::Reload );

	//Repeating
	input->BindAction( RepeatingAction , ETriggerEvent::Started , this , &UPlayerFireComp::ChangeRepeating );

}


void UPlayerFireComp::ChoosePistol()
{
	ServerRPCSelectedPistol(pistol);
}

void UPlayerFireComp::ChooseRifle()
{
	ServerRPCSelectedRifle(rifle);
}

void UPlayerFireComp::SpawnPistol(TSubclassOf<APistolGun> GunFactory)
{
	if(!me ){return;}

	if (GunFactory)
	{
		pistol = GetWorld()->SpawnActor<APistolGun>( GunFactory , FVector( 0 , 0 , 10000 ) , FRotator::ZeroRotator );

		if(pistol)
		{
			pistol->AttachToComponent( me->pistolComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
			pistol->SetOwner( me->GetController() );

			OnRep_Pistol();
		}
	}
}

void UPlayerFireComp::SpawnRifle(TSubclassOf<ARifleGun> rifleFactory)
{
	if(!me ){return;}

	if (rifleFactory)
	{
		rifle = GetWorld()->SpawnActor<ARifleGun>( rifleFactory , FVector( 0 , 0 , 10000 ) , FRotator::ZeroRotator );

		if(rifle)
		{
			rifle->AttachToComponent( me->rifleComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
			rifle->SetOwner( me->GetController() );

			OnRep_Rifle();
		}
	}

}

void UPlayerFireComp::Zoom()
{
	//me->FollowCamera->FieldOfView = FMath::Lerp<float>( me->FollowCamera->FieldOfView , targetFOV , me->GetWorld()->GetDeltaSeconds() * 10 );

	if (bAimRifle)
	{
		FVector Pos = FMath::Lerp<FVector>( me->FollowCamera->GetRelativeLocation() , rifle->AimCamSocket->GetRelativeLocation()
		, me->GetWorld()->GetDeltaSeconds() * 10 );

		//me->FollowCamera->SetRelativeLocation(Pos);
		
	}
	else
	{
		if(bValidRifle)
		{
			FVector Pos = FMath::Lerp<FVector>( rifle->AimCamSocket->GetRelativeLocation() , me->FollowCamera->GetRelativeLocation(), me->GetWorld()->GetDeltaSeconds() * 10 );

			//weapon->rifleCamComp->SetRelativeLocation( Pos );
		}
	}

}

void UPlayerFireComp::ZoomIn()
{
	bAimRifle = true;
	if ( !me->FollowCamera || !rifle || !pistol ) return;
	if ( !bValidPistol && !bValidRifle ) return;

	//Zoom camera location by gun type
	switch (aim)
	{
		case EWeaponAim::RIFLE:
			me->FollowCamera->AttachToComponent( rifle->AimCamSocket , FAttachmentTransformRules::SnapToTargetIncludingScale );

		break;

		case EWeaponAim::PISTOL:
			me->FollowCamera->AttachToComponent( pistol->AimCamSocket , FAttachmentTransformRules::SnapToTargetIncludingScale );
		break;

		case EWeaponAim::MACHINEGUN:
		break;
	}
}

void UPlayerFireComp::ZoomOut()
{
	bAimRifle = false;
	if (!me->DefaultCamPos || !me->FollowCamera) return;

	//default camera location 
	me->FollowCamera->AttachToComponent( me->DefaultCamPos , FAttachmentTransformRules::SnapToTargetIncludingScale );
}

void UPlayerFireComp::Fire()
{
	if (false == bValidPistol && false == bValidRifle) return;

	//call fire function by gun type 
	switch (aim)
	{
	case EWeaponAim::RIFLE:		FireRifle();	break;
	case EWeaponAim::PISTOL:	FirePistol();	break;
	case EWeaponAim::MACHINEGUN:
		break;
	}

}


//When choose gun type, the function called
void UPlayerFireComp::SelectedRifle()
{
	/*
	bValidRifle = true;
	bValidPistol = false;
	bEnableRepeating = rifle->bEnableRepeating;

	aim = EWeaponAim::RIFLE;

	//rifle->GunMeshComp->SetVisibility(true);
	//pistol->pistolMesh->SetVisibility( false );
	*/
}

void UPlayerFireComp::SelectedPistol()
{
}

void UPlayerFireComp::SelectedMachineGun()
{
}

//When fire gun, the function called
void UPlayerFireComp::FireRifle()
{
	ServerRPCFireRifle();
}

void UPlayerFireComp::FirePistol()
{
	ServerRPCFirePistol();
}

void UPlayerFireComp::ChangeRepeating()
{
	if(bEnableRepeating)
	{
		bRepeated = !bRepeated;
	}
}

void UPlayerFireComp::PrintNetLog()
{
	//오너가 있는가
	FString owner = me->GetOwner() ? me->GetOwner()->GetName() : TEXT( "No Exist Owner" );
	//NetConnection 있는가?
	FString conn = me->GetNetConnection() ? TEXT( "Valid" ) : TEXT( "InValid" );

	//Local Role
	FString localRole = UEnum::GetValueAsString<ENetRole>( me->GetLocalRole() );

	//Remote Roll
	FString remoteRole = UEnum::GetValueAsString<ENetRole>( me->GetRemoteRole() );

	FString str = FString::Printf( TEXT( "Owner : %s \nConnection : %s\nLocalRole : %s\nRemoteRole : %s" ) , *owner , *conn , *localRole , *remoteRole );

	FVector loc = me->GetActorLocation() + FVector( 0 , 0 , 50 );
	DrawDebugString( GetWorld() , loc , *str , nullptr , FColor::Yellow , 0 , true , 1.2f );
}


void UPlayerFireComp::SetAiming( FHitResult OutHit , FVector Start , FVector EndPoint )
{
	// Param Settings
	FCollisionQueryParams Params;
	Params.AddIgnoredActor( me );
	Params.AddIgnoredActor( rifle );
	Params.AddIgnoredActor( pistol );

	// Damage Setting
	float attackDamage = 0.0f;
	switch (aim)
	{
	case EWeaponAim::RIFLE:
		attackDamage = rifle->gunCP;
		break;
	case EWeaponAim::PISTOL:
		attackDamage = pistol->gunCP;
		break;
	case EWeaponAim::MACHINEGUN:
		break;
	}

	bool bHits = GetWorld()->LineTraceSingleByChannel( OutHit , Start , EndPoint , ECollisionChannel::ECC_Visibility , Params );

	UE_LOG( LogTemp , Warning , TEXT( "%s" ) , *OutHit.Component->GetName() );
	// Call a Take Damage function
	UCapsuleComponent* HitComp = Cast<UCapsuleComponent>( OutHit.GetComponent() );
	if (HitComp == nullptr)return;

	if (HitComp->ComponentHasTag( "Head" ) || HitComp->ComponentHasTag( "Thorax" ) || HitComp->ComponentHasTag( "Stomach" ) || HitComp->ComponentHasTag( "RightArm" ) || HitComp->ComponentHasTag( "LeftArm" ) || HitComp->ComponentHasTag( "RightLeg" ) || HitComp->ComponentHasTag( "LeftLeg" ))
	{
		auto otherplayer = Cast<APlayerBase>( OutHit.GetActor() );
		if (otherplayer)
		{
			FName BodyPart = HitComp->ComponentTags[0];
			FString HitObjectName = OutHit.GetComponent()->GetName();
			otherplayer->HealthComp->TakeDamage( BodyPart , attackDamage , HitObjectName );
		}
	}
	
}

void UPlayerFireComp::Reload()
{
	if(!this->rifle || !pistol) return;

	
	switch (aim)
	{
	case EWeaponAim::RIFLE:
		PlayerAnim->playReloadRifleAnimation();
		//rifle->currentAmmo = rifle->gunMaxAmmo;
		break;
	case EWeaponAim::PISTOL:
		PlayerAnim->playReloadPistolAnimation();
		//pistol->currentAmmo = pistol->gunMaxAmmo;
		break;
	case EWeaponAim::MACHINEGUN:
		break;

	}
	

	ServerRPCReload();

}

void UPlayerFireComp::ServerRPCSelectedPistol_Implementation( APistolGun* selectedPistol )
{
	MultiRPCSelectedPistol( selectedPistol );
}

void UPlayerFireComp::MultiRPCSelectedPistol_Implementation( APistolGun* selectedPistol )
{
	bValidPistol = true;
	bValidRifle = false;
	if(selectedPistol)
	{
		bEnableRepeating = selectedPistol->bEnableRepeating;
	}

	aim = EWeaponAim::PISTOL;

	OnRep_Pistol();
	OnRep_Rifle();


}

void UPlayerFireComp::ServerRPCFirePistol_Implementation()
{
	// Ammo Cnt
	if (pistol->currentAmmo <= 0) return;
	pistol->currentAmmo--;
	UE_LOG( LogTemp , Warning , TEXT( "%d" ) , pistol->currentAmmo );

	// Gun Start, End Point Settings
	AimStartPoint = pistol->pistolMesh->GetSocketLocation( TEXT( "Muzzle" ) );
	AimEndPoint = pistol->AimCamSocket->GetForwardVector() * 100000;

	// Param Settings
	FCollisionQueryParams Params;
	Params.AddIgnoredActor( me );
	Params.AddIgnoredActor( rifle );
	Params.AddIgnoredActor( pistol );

	// Aim, Fire Network Connection
	FHitResult OutHit;
	bool bHits = GetWorld()->LineTraceSingleByChannel( OutHit , AimStartPoint , AimEndPoint , ECollisionChannel::ECC_Visibility , Params );
	MultiRPCFirePistol( OutHit );
	SetAiming( OutHit , AimStartPoint , AimEndPoint );

}

void UPlayerFireComp::MultiRPCFirePistol_Implementation( FHitResult OutHits )
{
	// Montage Play
	PlayerAnim->playFirePistolAnimation();

	// Param Settings
	FCollisionQueryParams Params;
	Params.AddIgnoredActor( me );
	Params.AddIgnoredActor( rifle );
	Params.AddIgnoredActor( pistol );

	// Client Gun Start, End Point Settings
	FTransform t = pistol->pistolMesh->GetSocketTransform( TEXT( "Muzzle" ) );
	FVector _Start = pistol->pistolMesh->GetSocketLocation( TEXT( "Muzzle" ) );
	FVector _End = pistol->AimCamSocket->GetForwardVector() * 100000;
	bool bHits = GetWorld()->LineTraceSingleByChannel( OutHits , _Start , _End , ECollisionChannel::ECC_Visibility , Params );

	DrawDebugLine( GetWorld() , t.GetLocation() , _End , FColor::Silver , false , 0.2f );
	UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , ExplosionVFXFactory, OutHits.ImpactPoint);

	PlaySoundAtLocation();

}

void UPlayerFireComp::ServerRPCFireRifle_Implementation()
{
	// Ammo Cnt
	if (rifle->currentAmmo <= 0) return;
	rifle->currentAmmo--;
	UE_LOG( LogTemp , Warning , TEXT( "%d" ) , rifle->currentAmmo );

	// Gun Start, End Point Settings
	AimStartPoint = rifle->GunMeshComp->GetSocketLocation( TEXT( "Muzzle" ) );
	AimEndPoint = rifle->AimCamSocket->GetForwardVector() * 100000;

	// Param Settings
	FCollisionQueryParams Params;
	Params.AddIgnoredActor( me );
	Params.AddIgnoredActor( rifle );
	Params.AddIgnoredActor( pistol );

	// Aim, Fire Network Connection
	FHitResult OutHit;
	bool bHits = GetWorld()->LineTraceSingleByChannel( OutHit , AimStartPoint , AimEndPoint , ECollisionChannel::ECC_Visibility , Params );
	MultiRPCFireRifle( OutHit );
	SetAiming( OutHit , AimStartPoint , AimEndPoint );
}

void UPlayerFireComp::MultiRPCFireRifle_Implementation( FHitResult OutHits )
{
	PlayerAnim->playFireRifleAnimation();

	// Param Settings
	FCollisionQueryParams Params;
	Params.AddIgnoredActor( me );
	Params.AddIgnoredActor( rifle );
	Params.AddIgnoredActor( pistol );

	// Client Gun Start, End Point Settings
	FTransform t = rifle->GunMeshComp->GetSocketTransform( TEXT( "Muzzle" ) );
	FVector _Start = rifle->GunMeshComp->GetSocketLocation( TEXT( "Muzzle" ) );
	FVector _End = rifle->AimCamSocket->GetForwardVector() * 100000;
	bool bHits = GetWorld()->LineTraceSingleByChannel( OutHits , _Start , _End , ECollisionChannel::ECC_Visibility , Params );

	DrawDebugLine( GetWorld() , t.GetLocation() , _End , FColor::Silver , false , 0.2f );
	UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , ExplosionVFXFactory , OutHits.ImpactPoint );

	PlaySoundAtLocation();

}

void UPlayerFireComp::ServerRPCReload_Implementation()
{
	switch (aim)
	{
	case EWeaponAim::RIFLE:
		PlayerAnim->playReloadRifleAnimation();
		rifle->currentAmmo = rifle->gunMaxAmmo;
		break;
	case EWeaponAim::PISTOL:
		PlayerAnim->playReloadPistolAnimation();
		pistol->currentAmmo = pistol->gunMaxAmmo;
		break;
	case EWeaponAim::MACHINEGUN:
		break;

	}

	//MultiRPCReload();
}

void UPlayerFireComp::MultiRPCReload_Implementation()
{
	/*
	switch (aim)
	{
	case EWeaponAim::RIFLE:
		PlayerAnim->playReloadRifleAnimation();
		//rifle->currentAmmo = rifle->gunMaxAmmo;
		break;
	case EWeaponAim::PISTOL:
		PlayerAnim->playReloadPistolAnimation();
		//pistol->currentAmmo = pistol->gunMaxAmmo;
		break;
	case EWeaponAim::MACHINEGUN:
		break;

	}
	*/
}


void UPlayerFireComp::ServerRPCSelectedRifle_Implementation( ARifleGun* selectedRifle )
{
	MultiRPCSelectedRifle( selectedRifle );
}

void UPlayerFireComp::MultiRPCSelectedRifle_Implementation( ARifleGun* selectedRifle )
{
	bValidRifle = true;
	bValidPistol = false;
	if (selectedRifle)
	{
		bEnableRepeating = selectedRifle->bEnableRepeating;
	}

	aim = EWeaponAim::RIFLE;

	OnRep_Pistol();
	OnRep_Rifle();
}

void UPlayerFireComp::OnRep_Rifle()
{
	// Visible setting
	rifle->GunMeshComp->SetVisibility( bValidRifle );

	if (bValidRifle)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlayerFireComp::OnRep_Rifle - bValidRifle = true"))
	}
	else
	{
		UE_LOG( LogTemp , Warning , TEXT( "UPlayerFireComp::OnRep_Rifle - bValidRifle = false" ) )
	}

	// Ammo setting
	

}

void UPlayerFireComp::OnRep_Pistol()
{
	pistol->pistolMesh->SetVisibility( bValidPistol );
	//pistol->SetOwner(me);
	
}

void UPlayerFireComp::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( UPlayerFireComp , rifle );
	DOREPLIFETIME( UPlayerFireComp , bValidRifle );
	DOREPLIFETIME( UPlayerFireComp , pistol );
	DOREPLIFETIME( UPlayerFireComp , bValidPistol );
	DOREPLIFETIME( UPlayerFireComp , bAimRifle );
	//AimEndPoint
	DOREPLIFETIME( UPlayerFireComp , AimEndPoint );
	DOREPLIFETIME( UPlayerFireComp , AimStartPoint );
	//DOREPLIFETIME( UPlayerFireComp , pistol->currentAmmo );
	//DOREPLIFETIME( UPlayerFireComp , rifle->currentAmmo );

}
 
void UPlayerFireComp::PlaySoundAtLocation()
{
	UE_LOG( LogTemp , Warning , TEXT( "bang" ) );
	if (SoundToPlay != nullptr)
	{
		AudioComponent->SetSound( SoundToPlay );
		if (SoundAttenuation != nullptr)
		{
			AudioComponent->AttenuationSettings = SoundAttenuation;
		}
		AudioComponent->Play( 0.f );
	}

	//FireLightON
	FOutputDeviceNull pAR;
	GetOwner()->CallFunctionByNameWithArguments( TEXT( "FireLightON" ) , pAR , nullptr , true );

}
