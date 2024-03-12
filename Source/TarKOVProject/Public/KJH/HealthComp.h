// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusEffectComp.h"
#include "Components/ActorComponent.h"
#include "HealthComp.generated.h"


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

	// 각 신체 부위별 현재 HP
	UPROPERTY( EditDefaultsOnly , Category = "Health" )
	TMap<FName , float> BodyPartHP;

	// 각 신체 부위별 Max HP
	UPROPERTY( EditDefaultsOnly , Category = "Health" )
	TMap<FName , float> BodyPartMaxHP;

	


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 캐릭터의 사망 상태
	UPROPERTY( EditDefaultsOnly , Category = "Health" )
	bool bIsDead;


	void TakeDamage( const FName& BodyPart , float DamageAmount, const FString& HitObjectName );
	void CheckAndHandleTotalDepletion();
	void HealBodyPart( FName BodyPart , float HealAmount );
	// 상태이상에서 hp값 확인하기 위해
	float GetBodyPartHealth(FName BodyPart);
	float GetBodyPartMaxHealth(FName BodyPart );
	// 출혈 확인 및 적용을 위해
	void CheckAndApplyBleeding( const FName& BodyPart );
	// 골절 확인 및 적용 위해
	void CheckAndApplyFracture( const FName& BodyPart );
	// 피해 분산 함수
	void DistributeDamage( float DamageAmount , FName IgnoredBodyPart );




	UPROPERTY()
	class UStatusEffectComp* statusComp;

};
