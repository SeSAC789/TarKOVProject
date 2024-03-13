// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/PostProcessVolume.h"
#include "PainPostProcess.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API APainPostProcess : public APostProcessVolume
{
	GENERATED_BODY()


public:
  
    APainPostProcess();

    // 고통 효과를 활성화하거나 비활성화
    void EnablePainEffect( bool bEnable );

    UPROPERTY( VisibleAnywhere )
    class UPostProcessComponent* PostProcessComponent;

    void InitializePostProcessComponent();

    bool bIsPainEffectActive;

    FPostProcessSettings PainEffectSettings;

    // 고통 효과가 활성화되었는지 확인하는 함수
    bool IsPainEffectActive() const;
};
