// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HPWidget.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	class UProgressBar* HeadHp_Bar;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UProgressBar* LeftLegHp_Bar;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UProgressBar* RightLegHp_Bar;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UProgressBar* StomachHp_Bar;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UProgressBar* ThoraxHp_Bar;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UProgressBar* LeftArmHp_Bar;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UProgressBar* RightArmHp_Bar;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float HeadHPPercent() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float LeftLegHPPercent() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float RightLegHPPercent() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float StomachHPPercent() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float ThoraxHPPercent() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float LeftArmHPPercent() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float RightArmHPPercent() const;

	/*UPROPERTY()
	class UHealthComp* healthComp;*/
};
