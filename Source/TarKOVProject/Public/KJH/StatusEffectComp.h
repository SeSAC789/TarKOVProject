// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    FName FracturedBodyPart; // 골절된 부위

    // 상태이상 부위가 어디인지 알기 위한 변수
    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    FName AffectedBodyPart;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Status Effects" )
    TArray<FStatusEffectData> StatusEffects;


public:
    // 새로운 상태이상을 캐릭터에 적용하는 함수
    void ApplyStatusEffect( EStatusEffectType NewEffectType, FName BodyPart );
    // 특정 상태이상을 캐릭터에서 제거하거나 비활성화하는 함수
    void ClearStatusEffect( EStatusEffectType EffectType );
    // 모든 활성 상태이상을 업데이트
    void UpdateStatusEffects( float DeltaTime );

    // 상태이상별 효과 처리 함수 (구현 필요)
    void ApplyBleedingEffect( FStatusEffectData& EffectData , float DeltaTime );
    void ApplyFractureEffect( FStatusEffectData& EffectData , float DeltaTime );
    void ApplyPainEffect( FStatusEffectData& EffectData , float DeltaTime );

    UFUNCTION( BlueprintCallable , Category = "Status Effects" )
    bool IsBleeding() const;

    UPROPERTY()
    class UHealthComp* healthComp;

    UPROPERTY()
    class APlayerBase* me;
		
};
