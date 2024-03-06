// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerComp/PlayerFireComp.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/SpringArmComponent.h"
#include "JYJ/Weapon/RifleActor.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/Animation/PlayerAnimInstance.h"
#include "JYJ/TestPlayer/YJTestPlayer.h"
#include "Kismet/GameplayStatics.h"

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

	//ZoomIn
	input->BindAction( ZoomAction , ETriggerEvent::Started , this , &UPlayerFireComp::ZoomIn );
	input->BindAction( ZoomAction , ETriggerEvent::Completed , this , &UPlayerFireComp::ZoomOut );

	//Fire
	input->BindAction( FireAction , ETriggerEvent::Started , this , &UPlayerFireComp::Fire );


}

void UPlayerFireComp::ChoosePistol()
{
}

void UPlayerFireComp::ChooseRifle()
{
	AttachRifle( rifle );
}

void UPlayerFireComp::AttachRifle( TSubclassOf<ARifleActor> rifleFactory )
{
	UE_LOG( LogTemp , Warning , TEXT( "TEST1" ) );
	if (rifleFactory)
	{
		//const USkeletalMeshSocket* rifleSocket = me->GetMesh()->GetSocketByName("RifleSocket");
		//(X=-1.474972,Y=-9.100097,Z=7.645357)
		//(Pitch=80.757243,Yaw=88.039639,Roll=-78.615505)
		//weapon = GetWorld()->SpawnActor<ARifleActor>(FVector( -1.474972 , -9.100097 , 7.645357 ) , FRotator( 80.757243 , 88.039639 , 78.615505 ));
		weapon = GetWorld()->SpawnActor<ARifleActor>( rifleFactory, FVector( 0 , 0 , 10000 ) , FRotator::ZeroRotator );
		weapon->AttachToComponent( me->rifleComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );

		UE_LOG( LogTemp , Warning , TEXT( "TEST2" ) );

		//rifleSocket->AttachActor(weapon, me->GetMesh());
		bValidRifle = true;
	}
}

void UPlayerFireComp::Zoom()
{
	me->FollowCamera->FieldOfView = FMath::Lerp<float>( me->FollowCamera->FieldOfView , targetFOV , me->GetWorld()->GetDeltaSeconds() * 10 );

	if (bAimRifle)
	{
		/*
		FVector Pos = FMath::Lerp<FVector>( me->DefaultCamPos->GetRelativeLocation(), me->aimingCamPos->GetRelativeLocation()
		, me->GetWorld()->GetDeltaSeconds() * 10 );

		me->FollowCamera->SetRelativeLocation(Pos);
		*/
	}
	else
	{
		/*
		FVector Pos = FMath::Lerp<FVector>( me->aimingCamPos->GetRelativeLocation() , me->DefaultCamPos->GetRelativeLocation()
		, me->GetWorld()->GetDeltaSeconds() * 10 );

		me->FollowCamera->SetRelativeLocation( Pos );
		*/

	}


}

void UPlayerFireComp::ZoomIn()
{
	UE_LOG( LogTemp , Warning , TEXT( "zoom test1" ) );
	//me->cameraComp->FieldOfView = FMath::Lerp<float>( me->cameraComp->FieldOfView , targetFOV , me->GetWorld()->GetDeltaSeconds() * 10 );
	//testplayer->springComp->TargetArmLength = 30;

	/*FVector Pos = FMath::Lerp<FVector>( me->DefaultCamPos->GetRelativeLocation() , me->aimingCamPos->GetRelativeLocation()
		, me->GetWorld()->GetDeltaSeconds() * 10 );

	me->FollowCamera->SetRelativeLocation( Pos );*/

	bAimRifle = true;
	targetFOV = 50;
}

void UPlayerFireComp::ZoomOut()
{
	UE_LOG( LogTemp , Warning , TEXT( "zoom test2" ) );
	//testplayer->springComp->TargetArmLength = 0;

	bAimRifle = false;

	//FVector Pos = FMath::Lerp<FVector>( me->aimingCamPos->GetRelativeLocation() , me->DefaultCamPos->GetRelativeLocation()
	//	, me->GetWorld()->GetDeltaSeconds() * 10 );

	//me->FollowCamera->SetRelativeLocation( me->DefaultCamPos->GetRelativeLocation() );

	targetFOV = 90;
}

void UPlayerFireComp::Fire()
{

	if (bValidRifle)
	{
		FHitResult OutHit;
		//FVector Start = me->FollowCamera->GetComponentLocation();
		FVector Start = weapon->meshComp->GetSocketLocation( TEXT( "Muzzle" ) );
		//FVector End = Start + weapon->meshComp->GetForwardVector() * 100000;
		FVector End = me->FollowCamera->GetForwardVector() * 100000;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor( me );

		bool bHits = GetWorld()->LineTraceSingleByChannel( OutHit , Start , End , ECollisionChannel::ECC_Visibility , Params );

		//만약 부딪힌 곳이 있다면, 그 곳에 폭발 vfx를 배치하고 싶다.
		if (bHits)
		{
			FHitResult outhit;

			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , ExplosionVFXFactory , OutHit.ImpactPoint );
			FTransform t = weapon->meshComp->GetSocketTransform( TEXT( "Muzzle" ) );
			//DrawDebugLine( GetWorld() , t.GetLocation() , outhit.ImpactPoint , FColor::Silver , false , 0.2f );
			DrawDebugLine( GetWorld() , t.GetLocation() , End , FColor::Silver , false , 0.2f );

			//만약 부딪힌 상대방이 플레이어라면 데미지 함수를 호출
			auto otherplayer = Cast<APlayerBase>( OutHit.GetActor() );
			if (otherplayer)
			{
				//otherplayer->TakeDamage( 1 );
			}


		}
	}


}


