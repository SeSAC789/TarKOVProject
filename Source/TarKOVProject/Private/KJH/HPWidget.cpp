// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/HPWidget.h"

#include "Components/Image.h"
#include "JYJ/PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "KJH/HealthComp.h"

UHPWidget::UHPWidget(const FObjectInitializer& ObjectInitializer)
{

}

void UHPWidget::NativeTick( const FGeometry& MyGeometry , float InDeltaTime )
{
	Super::NativeTick( MyGeometry , InDeltaTime );
	
	if (Bleeding_Img)
	{
		Bleeding_Img->SetVisibility( GetBleedingVisibility() );
	}
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
