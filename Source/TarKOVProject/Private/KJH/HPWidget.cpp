// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/HPWidget.h"

#include "JYJ/PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "KJH/HealthComp.h"

float UHPWidget::HeadHPPercent() const
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

float UHPWidget::LeftLegHPPercent() const
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

float UHPWidget::RightLegHPPercent() const
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

float UHPWidget::StomachHPPercent() const
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

float UHPWidget::ThoraxHPPercent() const
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

float UHPWidget::LeftArmHPPercent() const
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

float UHPWidget::RightArmHPPercent() const
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
