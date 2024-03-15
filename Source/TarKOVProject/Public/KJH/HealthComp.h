// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusEffectComp.h"
#include "Components/ActorComponent.h"
#include "HealthComp.generated.h"

USTRUCT( BlueprintType )
struct FBodyPartHealthData
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FName BodyPart;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float HP;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float MaxHP;

	FBodyPartHealthData() : BodyPart( NAME_None ) , HP( 0.0f ) , MaxHP( 0.0f ) {}

	FBodyPartHealthData( FName InBodyPartName , float InCurrentHealth , float InMaxHealth )
		: BodyPart( InBodyPartName ) , HP( InCurrentHealth ) , MaxHP( InMaxHealth ) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TARKOVPROJECT_API UHealthComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:

	//// 각 신체 부위별 현재 HP
	//UPROPERTY( EditDefaultsOnly , Category = "Health" )
	//TMap<FName , float> BodyPartHP;

	//// 각 신체 부위별 Max HP
	//UPROPERTY( EditDefaultsOnly , Category = "Health" )
	//TMap<FName , float> BodyPartMaxHP;


	UPROPERTY( ReplicatedUsing = OnRep_BodyPartHP , EditDefaultsOnly , Category = "Health" )
	TArray<FBodyPartHealthData> BodyPartHP;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 캐릭터의 사망 상태
	UPROPERTY( Replicated, EditDefaultsOnly , Category = "Health" )
	bool bIsDead;


	void TakeDamage( const FName& BodyPart , float DamageAmount, const FString& HitObjectName );
	void CheckAndHandleTotalDepletion();
	void HealBodyPart( FName BodyPart , float HealAmount );
	bool IsInjured(FName BodyPart) const;
	// 상태이상에서 hp값 확인하기 위해
	float GetBodyPartHealth(FName BodyPart);
	float GetBodyPartMaxHealth(FName BodyPart );
	void SetBodyPartHP( FName BodyPart , float NewHP );

	UFUNCTION()
	void OnRep_BodyPartHP();

	// 출혈 확인 및 적용을 위해
	void CheckAndApplyBleeding( const FName& BodyPart );
	// 골절 확인 및 적용 위해
	void CheckAndApplyFracture( const FName& BodyPart );
	// 피해 분산 함수
	void DistributeDamage( float DamageAmount , FName IgnoredBodyPart );

	// 가장 체력이 적은 부위를 찾는 함수
	FName FindWeakestBodyPart();

	// 출혈 상태이상이 있는 모든 신체 부위의 이름을 반환하는 함수
	TArray<FName> GetBleedingBodyParts() const;

	TArray<FName> GetFracturedBodyParts() const;

	UPROPERTY()
	class UStatusEffectComp* statusComp;

	UPROPERTY()
	class UHPWidget* hpUI;

	UPROPERTY()
	class APlayerBase* me;

	virtual  void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	UFUNCTION(BlueprintCallable)
	void invenDie();

	UPROPERTY()
	class UGameOverWidget* GameOverUI;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> GameOverUIFactory;
};
