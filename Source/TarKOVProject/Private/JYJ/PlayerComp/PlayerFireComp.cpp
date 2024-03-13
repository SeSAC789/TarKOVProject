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



void UPlayerFireComp::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnim = Cast<UPlayerAnimInstance>( me->GetMesh()->GetAnimInstance() );
	check( PlayerAnim );

	//Spawn weapon
	//SpawnPistol(PistolGun);
	//ServerRPCSpawnPistol(PistolGun);
	//SpawnRifle( RifleGun );

	bRepeated = false;
	bAimRifle = false;

}

void UPlayerFireComp::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );
	//Zoom();

	//UE_LOG(LogTemp, Warning, TEXT("1"));
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
	//SelectedPistol();
}

void UPlayerFireComp::ChooseRifle()
{
	ServerRPCSelectedRifle(rifle);
	//SelectedRifle();
}

void UPlayerFireComp::SpawnPistol(TSubclassOf<APistolGun> GunFactory)
{
	if(!me){return;}

	if (GunFactory)
	{
		pistol = GetWorld()->SpawnActor<APistolGun>( GunFactory , FVector( 0 , 0 , 10000 ) , FRotator::ZeroRotator );
		if(pistol)
		{
			pistol->AttachToComponent( me->pistolComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
			pistol->SetOwner( me );
			pistol->pistolMesh->SetVisibility( false );
		}
		//ServerRPCSpawnPistol(GunFactory);

	}
	

}

void UPlayerFireComp::SpawnRifle(TSubclassOf<ARifleGun> rifleFactory)
{

	if(!me ){return;}

	if (rifleFactory)
	{
		rifle = GetWorld()->SpawnActor<ARifleGun>( rifleFactory , FVector( 0 , 0 , 10000 ) , FRotator::ZeroRotator );
		rifle->AttachToComponent( me->rifleComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
		rifle->GunMeshComp->SetVisibility( false );

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
	if (!me->FollowCamera) return;

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
	bValidRifle = true;
	bValidPistol = false;
	bEnableRepeating = rifle->bEnableRepeating;

	aim = EWeaponAim::RIFLE;

	rifle->GunMeshComp->SetVisibility(true);
	pistol->pistolMesh->SetVisibility( false );
}

void UPlayerFireComp::SelectedPistol()
{
	/*
	bValidPistol = true;
	bValidRifle = false;
	bEnableRepeating = pistol->bEnableRepeating;

	aim = EWeaponAim::PISTOL;

	if(pistol)
	{
		pistol->pistolMesh->SetVisibility( true );
	}
	if(rifle)
	{
		rifle->GunMeshComp->SetVisibility( false );
	}
	*/
}

void UPlayerFireComp::SelectedMachineGun()
{
}

//When fire gun, the function called
void UPlayerFireComp::FireRifle()
{

	if (rifle->currentAmmo <= 0) return;
	rifle->currentAmmo--;

	FHitResult OutHit;
	FVector Start = rifle->GunMeshComp->GetSocketLocation( TEXT( "Muzzle" ) );

	PlayerAnim->playFireRifleAnimation();

	if (!me->fireComp->bAimRifle)
	{
		FVector End = me->FollowCamera->GetForwardVector() * 100000;
		SetAiming( OutHit , Start , End );
	}
	else
	{
		FVector End = rifle->AimCamSocket->GetForwardVector() * 100000;
		SetAiming( OutHit , Start , End );
	}

}

void UPlayerFireComp::FirePistol()
{

	/*
	if (pistol->currentAmmo <= 0) return;
	pistol->currentAmmo--;
	UE_LOG( LogTemp , Warning , TEXT( "%d" ) , pistol->currentAmmo );

	FHitResult OutHit;
	FVector Start = pistol->pistolMesh->GetSocketLocation( TEXT( "Muzzle" ) );

	PlayerAnim->playFirePistolAnimation();

	if (!me->fireComp->bAimRifle)
	{
		FVector End = me->FollowCamera->GetForwardVector() * 100000;
		SetAiming( OutHit , Start , End );
	}
	else
	{
		FVector End = pistol->AimCamSocket->GetForwardVector() * 100000;
		SetAiming( OutHit , Start , End );
	}
	*/

	ServerRPCFirePistol();

}

void UPlayerFireComp::ChangeRepeating()
{
	if(bEnableRepeating)
	{
		bRepeated = !bRepeated;
	}
}


void UPlayerFireComp::SetAiming( FHitResult OutHit , FVector Start , FVector EndPoint )
{
	FCollisionQueryParams Params;

	Params.AddIgnoredActor( me );
	Params.AddIgnoredActor( rifle );
	Params.AddIgnoredActor( pistol );

	bool bHits = GetWorld()->LineTraceSingleByChannel( OutHit , Start , EndPoint , ECollisionChannel::ECC_Visibility , Params );

	if (bHits)
	{
		//UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , ExplosionVFXFactory , OutHit.ImpactPoint );

		FTransform t;
		float attackDamage = 0.0f;

		//Setting start socket
		switch (aim)
		{
		case EWeaponAim::RIFLE:
			t = rifle->GunMeshComp->GetSocketTransform( TEXT( "Muzzle" ) );
			attackDamage = rifle->gunCP;
			break; 
		case EWeaponAim::PISTOL:
			t = pistol->pistolMesh->GetSocketTransform( TEXT( "Muzzle" ) );
			attackDamage = pistol->gunCP;
			break;
		case EWeaponAim::MACHINEGUN:
			break;
		}

		DrawDebugLine( GetWorld() , t.GetLocation() , EndPoint , FColor::Silver , false , 0.2f );
		UE_LOG( LogTemp , Warning , TEXT( "%s" ) , *OutHit.Component->GetName() );

		UCapsuleComponent* HitComp = Cast<UCapsuleComponent>( OutHit.GetComponent() );
		if (HitComp == nullptr)return;

		if (HitComp->ComponentHasTag( "Head" ) || HitComp->ComponentHasTag( "Thorax" ) || HitComp->ComponentHasTag( "Stomach" ) || HitComp->ComponentHasTag( "RightArm" ) || HitComp->ComponentHasTag( "LeftArm" ) || HitComp->ComponentHasTag( "RightLeg" ) || HitComp->ComponentHasTag( "LeftLeg" ))
		{
			//만약 부딪힌 상대방이 플레이어라면 데미지 함수를 호출
			auto otherplayer = Cast<APlayerBase>( OutHit.GetActor() );
			if (otherplayer)
			{
				FName BodyPart = HitComp->ComponentTags[0];
				FString HitObjectName = OutHit.GetComponent()->GetName();
				otherplayer->HealthComp->TakeDamage( BodyPart , attackDamage , HitObjectName );
			}
		}

	}

	MultiRPCFirePistol(bHits, OutHit);
}

void UPlayerFireComp::Reload()
{
	switch (aim)
	{
		case EWeaponAim::RIFLE:
			//PlayerAnim->playReloadRifleAnimation();
			rifle->currentAmmo = rifle->gunMaxAmmo;
			break;
		case EWeaponAim::PISTOL:
			//PlayerAnim->playReloadPistolAnimation();
			pistol->currentAmmo = pistol->gunMaxAmmo;
			break;
		case EWeaponAim::MACHINEGUN:
			break;

	}

	ServerRPCReload();
}



void UPlayerFireComp::ServerRPCSpawnPistol_Implementation( TSubclassOf<APistolGun> GunFactory )
{
	UE_LOG( LogTemp , Warning , TEXT( "UPlayerFireComp::ServerRPCSpawnPistol_Implementation %s" ), *GetOwner()->GetName() );


	if (GunFactory)
	{
		pistol = GetWorld()->SpawnActor<APistolGun>( GunFactory , FVector( 0 , 0 , 10000 ) , FRotator::ZeroRotator );
		if(pistol)
		{
			pistol->AttachToComponent( me->pistolComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
			pistol->SetOwner( me );
			pistol->pistolMesh->SetVisibility( false );

			//Debug
			if (pistol->pistolMesh->GetVisibleFlag())
			{
				UE_LOG( LogTemp , Warning , TEXT( "UPlayerFireComp::ServerRPCSpawnPistol_Implementation - Visible" ) );
			}
			else
			{
				UE_LOG( LogTemp , Warning , TEXT( "UPlayerFireComp::ServerRPCSpawnPistol_Implementation - Not Visible" ) );
			}
			UE_LOG( LogTemp , Warning , TEXT( "UPlayerFireComp::ServerRPCSpawnPistol_Implementation: Owner: %s" ) , *pistol->GetOwner()->GetName() );

		}
		
	}

	MultiRPCSpawnPistol( pistol );
}

void UPlayerFireComp::MultiRPCSpawnPistol_Implementation( APistolGun* OwnPistol )
{
	if (!OwnPistol || !me->pistolComp)
	{
		return;
	}

	//pistolmesh->SetVisibility( false );
	OwnPistol->AttachToComponent( me->pistolComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
	OwnPistol->SetOwner( me );
	UE_LOG( LogTemp , Warning , TEXT( "UPlayerFireComp::MultiRPCSpawnPistol_Implementation: Owner: %s" ) , *OwnPistol->GetOwner()->GetName() );
	OwnPistol->pistolMesh->SetVisibility( false );
	if(OwnPistol->pistolMesh->GetVisibleFlag())
	{
		UE_LOG( LogTemp , Warning , TEXT( "UPlayerFireComp::MultiRPCSpawnPistol_Implementation - Visible" ) );
	}
	else
	{
		UE_LOG( LogTemp , Warning , TEXT( "UPlayerFireComp::MultiRPCSpawnPistol_Implementation - Not Visible" ) );
	}
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

	if (selectedPistol)
	{
		selectedPistol->pistolMesh->SetVisibility( true );
	}

	if (rifle)
	{
		rifle->GunMeshComp->SetVisibility( false );
	}
}

void UPlayerFireComp::ServerRPCFirePistol_Implementation()
{
	if (pistol->currentAmmo <= 0) return;
	pistol->currentAmmo--;
	UE_LOG( LogTemp , Warning , TEXT( "%d" ) , pistol->currentAmmo );

	FHitResult OutHit;
	FVector Start = pistol->pistolMesh->GetSocketLocation( TEXT( "Muzzle" ) );

	if (!me->fireComp->bAimRifle)
	{
		FVector End = me->FollowCamera->GetForwardVector() * 100000;
		SetAiming( OutHit , Start , End );


		FCollisionQueryParams Params;

		Params.AddIgnoredActor( me );
		Params.AddIgnoredActor( rifle );
		Params.AddIgnoredActor( pistol );

		bool bHits = GetWorld()->LineTraceSingleByChannel( OutHit , Start , End , ECollisionChannel::ECC_Visibility , Params );

		MultiRPCFirePistol( bHits , OutHit );
	}
	else
	{
		FVector End = pistol->AimCamSocket->GetForwardVector() * 100000;
		SetAiming( OutHit , Start , End );
	}

	//MultiRPCFirePistol( bHits , OutHit);

}

void UPlayerFireComp::MultiRPCFirePistol_Implementation(bool bHit, const FHitResult& hitInfo)
{

	PlayerAnim->playFirePistolAnimation();

	if (bHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , ExplosionVFXFactory , hitInfo.ImpactPoint );
	}
}

void UPlayerFireComp::ServerRPCReload_Implementation()
{
	//Reload();
	MultiRPCReload();
}

void UPlayerFireComp::MultiRPCReload_Implementation()
{
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
}


void UPlayerFireComp::ServerRPCSelectedRifle_Implementation( ARifleGun* selectedRifle )
{
	MultiRPCSelectedRifle( selectedRifle );
}

void UPlayerFireComp::MultiRPCSelectedRifle_Implementation( ARifleGun* selectedRifle )
{
	bValidRifle = true;
	bValidPistol = false;
	bEnableRepeating = selectedRifle->bEnableRepeating;

	aim = EWeaponAim::RIFLE;

	selectedRifle->GunMeshComp->SetVisibility( true );
	if(pistol)
	{
		pistol->pistolMesh->SetVisibility( false );
	}
	

}


void UPlayerFireComp::MultiRPCSpawnRifle_Implementation( ARifleGun* OwnRifle )
{
}

void UPlayerFireComp::ServerRPCSpawnRifle_Implementation( TSubclassOf<ARifleGun> GunFactory )
{
}