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

	UHPWidget( const FObjectInitializer& ObjectInitializer );

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


	UFUNCTION( BlueprintCallable  )
	float HeadHP() const;

	UFUNCTION( BlueprintCallable  )
	float LeftLegHP() const;

	UFUNCTION( BlueprintCallable  )
	float RightLegHP() const;

	UFUNCTION( BlueprintCallable  )
	float StomachHP() const;

	UFUNCTION( BlueprintCallable  )
	float ThoraxHP() const;

	UFUNCTION( BlueprintCallable  )
	float LeftArmHP() const;

	UFUNCTION( BlueprintCallable  )
	float RightArmHP() const;

	UPROPERTY( EditDefaultsOnly, meta = (BindWidget))
	class UImage* Head_Bleeding_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* Thorax_Bleeding_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* Stomach_Bleeding_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* RightArm_Bleeding_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* LeftArm_Bleeding_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* RightLeg_Bleeding_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* LeftLeg_Bleeding_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* Bleeding_Img;

	
	UFUNCTION( BlueprintCallable  )
	ESlateVisibility GetBleedingVisibilityBodyPart( FName BodyPart ) const;

	UFUNCTION( BlueprintCallable  )
	ESlateVisibility GetBleedingVisibility() const;

	UFUNCTION( BlueprintCallable )
	ESlateVisibility GetFracturedVisibilityBodyPart( FName BodyPart ) const;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* Fracture_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* RightLeg_Fracture_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* LeftLeg_Fracture_Img;

	UFUNCTION( BlueprintCallable  )
	ESlateVisibility GetFractureVisibility() const;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* Pain_Img;

	UFUNCTION( BlueprintCallable  )
	ESlateVisibility GetPainVisibility() const;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* Head_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* Thorax_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* Stomach_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* LeftArm_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* RightArm_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* LeftLeg_Img;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* RightLeg_Img;

	UFUNCTION( BlueprintCallable )
	void UpdateBodyPartImageColor( UImage* BodyPartImage , float HPPercentage ) const;

	UFUNCTION( BlueprintCallable )
	void UpdateStatusText();

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UProgressBar* Stamina_Bar;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* Bleeding_Text;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* Fracture_Text;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidgetAnim),Transient )
	class UWidgetAnimation* HitAnimation;

	void PlayHitAnim();
	void UpdateStaminaBar();


	/*UPROPERTY()
	class UHealthComp* healthComp;*/
};
