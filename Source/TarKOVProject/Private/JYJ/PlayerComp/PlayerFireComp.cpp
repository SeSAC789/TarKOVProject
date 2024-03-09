// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerComp/PlayerFireComp.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/Animation/PlayerAnimInstance.h"
#include "JYJ/Weapon/RifleGun.h"
#include "Kismet/GameplayStatics.h"
#include "KJH/HealthComp.h"

void UPlayerFireComp::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnim = Cast<UPlayerAnimInstance>( me->GetMesh()->GetAnimInstance() );
	check( PlayerAnim );

}

void UPlayerFireComp::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );
	Zoom();
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


}

void UPlayerFireComp::ChoosePistol()
{
	bValidRifle = false;
}

void UPlayerFireComp::ChooseRifle()
{
	SpawnRifle(RifleGun);
}

void UPlayerFireComp::SpawnRifle(TSubclassOf<ARifleGun> rifleFactory)
{
	if (rifleFactory)
	{
		gun = GetWorld()->SpawnActor<ARifleGun>( rifleFactory , FVector( 0 , 0 , 10000 ) , FRotator::ZeroRotator );
		gun->AttachToComponent( me->rifleComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );

		bValidRifle = true;

	}
}

void UPlayerFireComp::Zoom()
{

	//줌 자연스럽게 lerp 하는 코드 -> 개선 필요
	
	//me->FollowCamera->FieldOfView = FMath::Lerp<float>( me->FollowCamera->FieldOfView , targetFOV , me->GetWorld()->GetDeltaSeconds() * 10 );

	if (bAimRifle)
	{
		FVector Pos = FMath::Lerp<FVector>( me->FollowCamera->GetRelativeLocation() , gun->AimCamSocket->GetRelativeLocation()
		, me->GetWorld()->GetDeltaSeconds() * 10 );

		//me->FollowCamera->SetRelativeLocation(Pos);
		
	}
	else
	{
		if(bValidRifle)
		{
			FVector Pos = FMath::Lerp<FVector>( gun->AimCamSocket->GetRelativeLocation() , me->FollowCamera->GetRelativeLocation(), me->GetWorld()->GetDeltaSeconds() * 10 );

			//weapon->rifleCamComp->SetRelativeLocation( Pos );
		}

	}
	


}

void UPlayerFireComp::ZoomIn()
{
	bAimRifle = true;

	if (!me->fireComp->bValidRifle || !me->FollowCamera) return;

	me->FollowCamera->AttachToComponent(gun->AimCamSocket , FAttachmentTransformRules::SnapToTargetIncludingScale );

}

void UPlayerFireComp::ZoomOut()
{

	bAimRifle = false;

	if (!me->fireComp->bValidRifle || !me->DefaultCamPos || !me->FollowCamera) return;

	me->FollowCamera->AttachToComponent( me->DefaultCamPos , FAttachmentTransformRules::SnapToTargetIncludingScale );


}

void UPlayerFireComp::Fire()
{
	if (me->fireComp->bValidRifle)
	{
		FHitResult OutHit;
		FVector Start = gun->GunMeshComp->GetSocketLocation( TEXT( "Muzzle" ) );

		PlayerAnim->playFireAnimation();

		if(!me->fireComp->bAimRifle)
		{
			FVector End = me->FollowCamera->GetForwardVector() * 100000;
			SetRifleAiming(OutHit, Start, End);
		}
		else 
		{
			FVector End = gun->AimCamSocket->GetForwardVector() * 100000;
			SetRifleAiming(OutHit, Start, End);
		}
	}
}

void UPlayerFireComp::SetRifleAiming(FHitResult OutHit, FVector Start, FVector EndPoint)
{
	FCollisionQueryParams Params;
	Params.AddIgnoredActor( me );
	Params.AddIgnoredActor( gun );

	bool bHits = GetWorld()->LineTraceSingleByChannel( OutHit , Start , EndPoint , ECollisionChannel::ECC_Visibility , Params );

	if (bHits)
	{
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , ExplosionVFXFactory , OutHit.ImpactPoint );

		FTransform t = gun->GunMeshComp->GetSocketTransform( TEXT( "Muzzle" ) );
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
				otherplayer->HealthComp->TakeDamage( BodyPart , gun->gunCP , HitObjectName );
			}
		}

	}
}


