// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/HPWidget.h"

#include "Components/Image.h"
#include "JYJ/PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "KJH/HealthComp.h"


UHPWidget::UHPWidget( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

}

void UHPWidget::NativeTick( const FGeometry& MyGeometry , float InDeltaTime )
{
	Super::NativeTick( MyGeometry , InDeltaTime );

	if (Bleeding_Img)
	{
		Bleeding_Img->SetVisibility( GetBleedingVisibility() );
	}

	if (Fracture_Img)
	{
		Fracture_Img->SetVisibility( GetFractureVisibility() );
	}

	if (Pain_Img)
	{
		Pain_Img->SetVisibility( GetPainVisibility() );
	}

	UpdateBodyPartImageColor( Head_Img , HeadHP() );
	UpdateBodyPartImageColor( Thorax_Img , ThoraxHP() );
	UpdateBodyPartImageColor( Stomach_Img , StomachHP() );
	UpdateBodyPartImageColor( LeftArm_Img , LeftArmHP() );
	UpdateBodyPartImageColor( RightArm_Img , RightArmHP() );
	UpdateBodyPartImageColor( LeftLeg_Img , LeftLegHP() );
	UpdateBodyPartImageColor( RightLeg_Img , RightLegHP() );
}

float UHPWidget::HeadHP() const
{
	APlayerBase* me = Cast<APlayerBase>( UGameplayStatics::GetPlayerCharacter( this , 0 ) );
	if (me)
	{
		UHealthComp* healthComp = Cast<UHealthComp>( me->GetComponentByClass( UHealthComp::StaticClass() ) );
		if (healthComp)
		{
			return healthComp->GetBodyPartHealth( "Head" ) / healthComp->GetBodyPartMaxHealth( "Head" );

		}
	}
	return 0.0f;
}

float UHPWidget::LeftLegHP() const
{
	APlayerBase* me = Cast<APlayerBase>( UGameplayStatics::GetPlayerCharacter( this , 0 ) );
	if (me)
	{
		UHealthComp* healthComp = Cast<UHealthComp>( me->GetComponentByClass( UHealthComp::StaticClass() ) );
		if (healthComp)
		{
			return healthComp->GetBodyPartHealth( "LeftLeg" ) / healthComp->GetBodyPartMaxHealth( "LeftLeg" );
		}
	}
	return 0.0f;
}

float UHPWidget::RightLegHP() const
{
	APlayerBase* me = Cast<APlayerBase>( UGameplayStatics::GetPlayerCharacter( this , 0 ) );
	if (me)
	{
		UHealthComp* healthComp = Cast<UHealthComp>( me->GetComponentByClass( UHealthComp::StaticClass() ) );
		if (healthComp)
		{
			return healthComp->GetBodyPartHealth( "RightLeg" ) / healthComp->GetBodyPartMaxHealth( "RightLeg" );
		}
	}
	return 0.0f;
}

float UHPWidget::StomachHP() const
{
	APlayerBase* me = Cast<APlayerBase>( UGameplayStatics::GetPlayerCharacter( this , 0 ) );
	if (me)
	{
		UHealthComp* healthComp = Cast<UHealthComp>( me->GetComponentByClass( UHealthComp::StaticClass() ) );
		if (healthComp)
		{
			return healthComp->GetBodyPartHealth( "Stomach" ) / healthComp->GetBodyPartMaxHealth( "Stomach" );
		}
	}
	return 0.0f;
}

float UHPWidget::ThoraxHP() const
{
	APlayerBase* me = Cast<APlayerBase>( UGameplayStatics::GetPlayerCharacter( this , 0 ) );
	if (me)
	{
		UHealthComp* healthComp = Cast<UHealthComp>( me->GetComponentByClass( UHealthComp::StaticClass() ) );
		if (healthComp)
		{
			return healthComp->GetBodyPartHealth( "Thorax" ) / healthComp->GetBodyPartMaxHealth( "Thorax" );
		}
	}
	return 0.0f;
}

float UHPWidget::LeftArmHP() const
{
	APlayerBase* me = Cast<APlayerBase>( UGameplayStatics::GetPlayerCharacter( this , 0 ) );
	if (me)
	{
		UHealthComp* healthComp = Cast<UHealthComp>( me->GetComponentByClass( UHealthComp::StaticClass() ) );
		if (healthComp)
		{
			return healthComp->GetBodyPartHealth( "LeftArm" ) / healthComp->GetBodyPartMaxHealth( "LeftArm" );
		}
	}
	return 0.0f;
}

float UHPWidget::RightArmHP() const
{
	APlayerBase* me = Cast<APlayerBase>( UGameplayStatics::GetPlayerCharacter( this , 0 ) );
	if (me)
	{
		UHealthComp* healthComp = Cast<UHealthComp>( me->GetComponentByClass( UHealthComp::StaticClass() ) );
		if (healthComp)
		{
			return healthComp->GetBodyPartHealth( "RightArm" ) / healthComp->GetBodyPartMaxHealth( "RightArm" );
		}
	}
	return 0.0f;
}

ESlateVisibility UHPWidget::GetBleedingVisibility() const
{
	APlayerBase* me = Cast<APlayerBase>( GetOwningPlayerPawn() );
	if (me)
	{
		UStatusEffectComp* StatusEffectComp = me->FindComponentByClass<UStatusEffectComp>();
		if (StatusEffectComp && StatusEffectComp->IsBleeding())
		{
			return ESlateVisibility::Visible;
		}
	}
	return ESlateVisibility::Hidden;
}

ESlateVisibility UHPWidget::GetFractureVisibility() const
{
	APlayerBase* me = Cast<APlayerBase>( GetOwningPlayerPawn() );
	if (me)
	{
		UStatusEffectComp* StatusEffectComp = me->FindComponentByClass<UStatusEffectComp>();
		if (StatusEffectComp && StatusEffectComp->IsFractured())
		{
			return ESlateVisibility::Visible;
		}
	}
	return ESlateVisibility::Hidden;
}

ESlateVisibility UHPWidget::GetPainVisibility() const
{
	APlayerBase* me = Cast<APlayerBase>( GetOwningPlayerPawn() );
	if (me)
	{
		UStatusEffectComp* StatusEffectComp = me->FindComponentByClass<UStatusEffectComp>();
		if (StatusEffectComp && StatusEffectComp->IsPain())
		{
			return ESlateVisibility::Visible;
		}
	}
	return ESlateVisibility::Hidden;
}

void UHPWidget::UpdateBodyPartImageColor( UImage* BodyPartImage , float HPPercentage ) const
{
	FLinearColor Color;
	if (HPPercentage > 0.7f) // 100% ~ 70%
	{
		Color = FLinearColor::Green;
	}
	else if (HPPercentage > 0.3f) // 69% ~ 30%
	{
		Color = FLinearColor::Yellow;
	}
	else if (HPPercentage > 0) // 29% ~ 1%
	{
		Color = FLinearColor::Red;
	}
	else // 0%
	{
		Color = FLinearColor::Black;
	}

	if (BodyPartImage)
	{
		BodyPartImage->SetColorAndOpacity( Color );
	}
}

