// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PainPostProcess.h"
#include "Components/ActorComponent.h"
#include "JYJ/PlayerComp/PlayerMoveComp.h"
#include "StatusEffectComp.generated.h"

UENUM( BlueprintType )
enum class EStatusEffectType : uint8
{
	None         UMETA( DisplayName = "None" ) ,
	Bleeding     UMETA( DisplayName = "Bleeding" ) ,
	Fracture     UMETA( DisplayName = "Fracture" ) ,
	Pain         UMETA( DisplayName = "Pain" ) ,

};

USTRUCT( BlueprintType )
struct FStatusEffectData
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EStatusEffectType EffectType; // 상태이상의 유형

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bIsActive; // 상태이상 활성화 여부

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FName BodyPart; // 출혈이 적용되는 신체 부위

	float Timer = 0.0f; // 상태이상 타이머
	float RunningTimer = 0.0f; // 달리기 중 데미지 적용 타이머
	float PainTimer; // 고통 상태이상 타이머

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FName FracturedBodyPart; // 골절된 부위

	// 상태이상 부위가 어디인지 알기 위한 변수
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FName AffectedBodyPart;

	bool bIsSpeedModified = false; // 속도 조정이 이미 적용되었는지 확인하는 변수

};

UCLASS( ClassGroup = (Custom) , meta = (BlueprintSpawnableComponent) )
class TARKOVPROJECT_API UStatusEffectComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatusEffectComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction ) override;

protected:
	UPROPERTY( Replicated, VisibleAnywhere , BlueprintReadOnly , Category = "Status Effects" )
	TArray<FStatusEffectData> StatusEffects;


public:
	// 새로운 상태이상을 캐릭터에 적용하는 함수
	void ApplyStatusEffect( EStatusEffectType NewEffectType , FName BodyPart );
	// 특정 상태이상을 캐릭터에서 제거하거나 비활성화하는 함수
	void ClearStatusEffect( EStatusEffectType EffectType , FName BodyPart );
	// 모든 활성 상태이상을 업데이트
	void UpdateStatusEffects( float DeltaTime );

	// 상태이상별 효과 처리 함수 (구현 필요)
	void ApplyBleedingEffect( FStatusEffectData& EffectData , float DeltaTime );
	void ApplyFractureEffect( FStatusEffectData& EffectData , float DeltaTime );
	void ApplyPainEffect( FStatusEffectData& EffectData , float DeltaTime );


	UFUNCTION( BlueprintCallable , Category = "Status Effects" )
	bool IsBleeding( FName BodyPart ) const;

	UFUNCTION( BlueprintCallable , Category = "Status Effects" )
	bool IsFractured() const;

	bool IsPain() const;

	UPROPERTY()
	class UHealthComp* healthComp;

	UPROPERTY()
	class UPlayerMoveComp* moveComp;

	UPROPERTY()
	class APlayerBase* me;

	UPROPERTY()
	class APainPostProcess* painPost;

	FName FindWeakestBodyPart();
	int32 GetBleedingCount() const;
	int32 GetFractureCount() const;

	virtual  void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
};
