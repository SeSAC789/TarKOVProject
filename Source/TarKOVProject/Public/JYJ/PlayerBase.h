// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN( LogTemplateCharacter , Log , All );
DECLARE_MULTICAST_DELEGATE_OneParam( FSetupInputDelegate , class UEnhancedInputComponent* );

UCLASS( config = Game )
class APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	/** Follow camera */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true") )
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputMappingContext* DefaultMappingContext;


	APlayerBase();


public:
	// APawn interface
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;

	// To add mapping context
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHitboxOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	virtual void PossessedBy( AController* NewController ) override;

public:
	FSetupInputDelegate SetupInputDelegate;

	UPROPERTY( EditDefaultsOnly )
	class USceneComponent* aimingCamPos;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* DefaultCamPos;

	UPROPERTY( EditDefaultsOnly )
	class USceneComponent* rifleComp;

	UPROPERTY( EditDefaultsOnly )
	class USceneComponent* pistolComp;

	// 고통상태이상 위한 포스트프로세스 추가
	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite)
	class UPostProcessComponent* PainPostProcessComp;



public:
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	// 24.03.06 정현 플레이어 기능 추가
	// 정현이 테스트 플레이어에서 재정의 가능하도록 수정 -> 정현이한테 말하기
	//UFUNCTION()
	//void OnHitboxOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	// 머리
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* HeadHitbox;
	// 흉부
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* ThoraxHitbox;
	// 복부
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* StomachHitbox;
	// 오른팔
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* RightArmUpperHitbox;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* RightForeArmHitbox;
	// 왼팔
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftArmUpperHitbox;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftForeArmHitbox;
	// 오른다리
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* RightLegUpperHitbox;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* RightLegLowerHitbox;
	// 왼다리
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftLegUpperHitbox;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Hitbox" )
	class UCapsuleComponent* LeftLegLowerHitbox;

	// Components
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components" )
	class UHealthComp* HealthComp;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Components" )
	class UPlayerFireComp* fireComp;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Components" )
	class UPlayerMoveComp* moveComp;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Components" )
	class UStatusEffectComp* statusComp;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Components" )
	class UStaminaComp* staminaComp;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components" )
	class UPlayerThrowComp* throwComp;
	
	void SetPartitionDamageCollision();

	UPROPERTY( BlueprintReadOnly )
	class UHPWidget* PlayerMainUI;

	UPROPERTY()
	class UGameOverWidget* GameOverUI;

	UPROPERTY()
	class UGameClearWidget* GameClearUI;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> PlayerMainUIFactory;


	UFUNCTION( BlueprintImplementableEvent )
	void invenDie();
};

