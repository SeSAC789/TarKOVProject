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
	

	virtual void NativeTick( const FGeometry& MyGeometry , float InDeltaTime ) override;

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
	float HeadHP() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float LeftLegHP() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float RightLegHP() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float StomachHP() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float ThoraxHP() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float LeftArmHP() const;

	UFUNCTION( BlueprintCallable , Category = "Health" )
	float RightArmHP() const;

	UPROPERTY( EditDefaultsOnly, meta = (BindWidget))
	class UImage* Bleeding_Img;

	// 출혈 상태를 확인하여 가시성을 반환하는 함수 선언
	UFUNCTION( BlueprintCallable , Category = "Health" )
	ESlateVisibility GetBleedingVisibility() const;

	/*UPROPERTY()
	class UHealthComp* healthComp;*/
};
