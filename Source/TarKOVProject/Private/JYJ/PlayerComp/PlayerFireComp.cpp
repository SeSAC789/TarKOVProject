// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerComp/PlayerFireComp.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/SpringArmComponent.h"
#include "JYJ/Weapon/RifleActor.h"
#include "JYJ/PlayerBase.h"
#include "JYJ/Animation/PlayerAnimInstance.h"
#include "JYJ/TestPlayer/YJTestPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "KJH/DamageTestActor.h"
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
	AttachRifle( rifle );
}

void UPlayerFireComp::AttachRifle( TSubclassOf<ARifleActor> rifleFactory )
{
	UE_LOG( LogTemp , Warning , TEXT( "TEST1" ) );
	if (rifleFactory)
	{
		weapon = GetWorld()->SpawnActor<ARifleActor>( rifleFactory, FVector( 0 , 0 , 10000 ) , FRotator::ZeroRotator );
		weapon->AttachToComponent( me->rifleComp , FAttachmentTransformRules::SnapToTargetNotIncludingScale );

		bValidRifle = true;
		
	}
}

void UPlayerFireComp::Zoom()
{

	//줌 자연스럽게 lerp 하는 코드 -> 개선 필요
	/*
	me->FollowCamera->FieldOfView = FMath::Lerp<float>( me->FollowCamera->FieldOfView , targetFOV , me->GetWorld()->GetDeltaSeconds() * 10 );

	if (bAimRifle)
	{
		FVector Pos = FMath::Lerp<FVector>( me->FollowCamera->GetRelativeLocation() , weapon->rifleCamComp->GetRelativeLocation()
		, me->GetWorld()->GetDeltaSeconds() * 10 );

		me->FollowCamera->SetRelativeLocation(Pos);
		
	}
	else
	{
		if(bValidRifle)
		{
			FVector Pos = FMath::Lerp<FVector>( weapon->rifleCamComp->GetRelativeLocation() , me->FollowCamera->GetRelativeLocation(), me->GetWorld()->GetDeltaSeconds() * 10 );

			weapon->rifleCamComp->SetRelativeLocation( Pos );
		}

	}
	*/


}

void UPlayerFireComp::ZoomIn()
{
	bAimRifle = true;

	if (!me->fireComp->bValidRifle) return;

	//카메라 시점 변경 (PlayerCam -> RifleCam)
	me->FollowCamera->Deactivate();
	auto pc = Cast<APlayerController>( me->GetController() );
	if (nullptr == pc) return;

	weapon->ActiveRifleCamp(bAimRifle, pc);
}

void UPlayerFireComp::ZoomOut()
{

	bAimRifle = false;

	if (!me->fireComp->bValidRifle) return;

	//카메라 시점 변경 (RifleCam -> PlayerCam)
	auto pc = Cast<APlayerController>( me->GetController() );
	if (nullptr == pc) return;

	pc->SetViewTargetWithBlend( me );
	me->FollowCamera->Activate(true);

}

void UPlayerFireComp::Fire()
{

	if (bValidRifle)
	{
		FHitResult OutHit;
		FVector Start = weapon->meshComp->GetSocketLocation( TEXT( "Muzzle" ) );
		//FVector End = weapon->rifleCamComp->GetForwardVector() * 100000;
		FVector End = me->FollowCamera->GetForwardVector() * 100000;

		FCollisionQueryParams Params;
		Params.AddIgnoredActor( me );

		bool bHits = GetWorld()->LineTraceSingleByChannel( OutHit , Start , End , ECollisionChannel::ECC_Visibility , Params );

		//만약 부딪힌 곳이 있다면, 그 곳에 폭발 vfx를 배치하고 싶다.
		if (bHits)
		{
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , ExplosionVFXFactory , OutHit.ImpactPoint );

			FTransform t = weapon->meshComp->GetSocketTransform( TEXT( "Muzzle" ) );
			DrawDebugLine( GetWorld() , t.GetLocation() , End , FColor::Silver , false , 0.2f );
			UE_LOG( LogTemp , Warning,TEXT( "%s" ) , *OutHit.Component->GetName() );

			//태호가 제시해준 방향
			
			UCapsuleComponent* HitComp = Cast<UCapsuleComponent>( OutHit.GetComponent() );
			if(HitComp==nullptr)return;

			if (HitComp->ComponentHasTag( "Head" ) || HitComp->ComponentHasTag( "Thorax" ) || HitComp->ComponentHasTag( "Stomach" ) || HitComp->ComponentHasTag( "RightArm" ) || HitComp->ComponentHasTag( "LeftArm" ) || HitComp->ComponentHasTag( "RightLeg" ) || HitComp->ComponentHasTag( "LeftLeg" ))
			{
				//FTransform t = weapon->meshComp->GetSocketTransform( TEXT( "Muzzle" ) );
				//FTransform aimSight = weapon->meshComp->GetSocketTransform( TEXT( "AimSight" ) );

				DrawDebugLine( GetWorld() , t.GetLocation() , End , FColor::Silver , false , 0.2f );

				//만약 부딪힌 상대방이 플레이어라면 데미지 함수를 호출
				auto otherplayer = Cast<APlayerBase>( OutHit.GetActor() );
				if (otherplayer)
				{

					FName BodyPart = HitComp->ComponentTags[0];
					FString HitObjectName = OutHit.GetComponent()->GetName();
					//HitComp->ComponentTags[0]
					me->HealthComp->TakeDamage( BodyPart, 5, HitObjectName );
					//GetWorld()->SpawnActor<ADamageTestActor>(DamageActor, OutHit.GetActor()->GetActorLocation(), FRotator::ZeroRotator);


				}
			}
			
			
			//FTransform t = weapon->meshComp->GetSocketTransform( TEXT( "Muzzle" ) );
			////FTransform aimSight = weapon->meshComp->GetSocketTransform( TEXT( "AimSight" ) );

			//DrawDebugLine( GetWorld() , t.GetLocation() , End , FColor::Silver , false , 0.2f );

			////만약 부딪힌 상대방이 플레이어라면 해당 위치에 스폰
			//auto otherplayer = Cast<APlayerBase>( OutHit.GetActor());
			//if (otherplayer)
			//{
			//	FActorSpawnParameters SpawnParameters;
			//	GetWorld()->SpawnActor<ADamageTestActor>( DamageActorFactory , OutHit.GetComponent()->GetComponentLocation() , FRotator::ZeroRotator , SpawnParameters );

			//}


		}
	}


}


