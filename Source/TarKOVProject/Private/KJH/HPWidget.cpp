// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/HPWidget.h"

#include "Components/Image.h"
#include "JYJ/PlayerBase.h"
#include "Kismet/GameplayStatics.h"
#include "KJH/HealthComp.h"
#include "Components/TextBlock.h"
#include "JYJ/Controller/TarKOVPlayerController.h"
#include "KJH/StaminaComp.h"


UHPWidget::UHPWidget( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{

}

void UHPWidget::NativeTick( const FGeometry& MyGeometry , float InDeltaTime )
{
	Super::NativeTick( MyGeometry , InDeltaTime );

	// 츨혈
	if (Head_Bleeding_Img) { Head_Bleeding_Img->SetVisibility( GetBleedingVisibilityBodyPart( TEXT( "Head" ) ) ); }
	if (Thorax_Bleeding_Img) { Thorax_Bleeding_Img->SetVisibility( GetBleedingVisibilityBodyPart( TEXT( "Thorax" ) ) ); }
	if (Stomach_Bleeding_Img) { Stomach_Bleeding_Img->SetVisibility( GetBleedingVisibilityBodyPart( TEXT( "Stomach" ) ) ); }
	if (RightArm_Bleeding_Img) { RightArm_Bleeding_Img->SetVisibility( GetBleedingVisibilityBodyPart( TEXT( "RightArm" ) ) ); }
	if (LeftArm_Bleeding_Img) { LeftArm_Bleeding_Img->SetVisibility( GetBleedingVisibilityBodyPart( TEXT( "LeftArm" ) ) ); }
	if (RightLeg_Bleeding_Img) { RightLeg_Bleeding_Img->SetVisibility( GetBleedingVisibilityBodyPart( TEXT( "RightLeg" ) ) ); }
	if (LeftLeg_Bleeding_Img) { LeftLeg_Bleeding_Img->SetVisibility( GetBleedingVisibilityBodyPart( TEXT( "LeftLeg" ) ) ); }

	if (Bleeding_Img) { Bleeding_Img->SetVisibility( GetBleedingVisibility() ); }

	// 골절
	if (RightLeg_Bleeding_Img) { RightLeg_Fracture_Img->SetVisibility( GetFracturedVisibilityBodyPart( TEXT( "RightLeg" ) ) ); }
	if (LeftLeg_Bleeding_Img) { LeftLeg_Fracture_Img->SetVisibility( GetFracturedVisibilityBodyPart( TEXT( "LeftLeg" ) ) ); }

	if (Fracture_Img) { Fracture_Img->SetVisibility( GetFractureVisibility() ); }



	//if (Pain_Img)
	//{
	//	Pain_Img->SetVisibility( GetPainVisibility() );
	//}

	UpdateBodyPartImageColor( Head_Img , HeadHP() );
	UpdateBodyPartImageColor( Thorax_Img , ThoraxHP() );
	UpdateBodyPartImageColor( Stomach_Img , StomachHP() );
	UpdateBodyPartImageColor( LeftArm_Img , RightArmHP() );
	UpdateBodyPartImageColor( RightArm_Img , LeftArmHP() );
	UpdateBodyPartImageColor( LeftLeg_Img , RightLegHP() );
	UpdateBodyPartImageColor( RightLeg_Img , LeftLegHP() );

	UpdateStatusText();
	if (Stamina_Bar)
	{
		UpdateStaminaBar();
	}


	UpdateHPBarColor( HeadHp_Bar , HeadHP() );
	UpdateHPBarColor( ThoraxHp_Bar , ThoraxHP() );
	UpdateHPBarColor( StomachHp_Bar , StomachHP() );
	UpdateHPBarColor( RightArmHp_Bar , RightArmHP() );
	UpdateHPBarColor( LeftArmHp_Bar , LeftArmHP() );
	UpdateHPBarColor( RightLegHp_Bar , RightLegHP() );
	UpdateHPBarColor( LeftLegHp_Bar , LeftLegHP() );
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

ESlateVisibility UHPWidget::GetBleedingVisibilityBodyPart( FName BodyPart ) const
{
	APlayerBase* me = Cast<APlayerBase>( GetOwningPlayerPawn() );
	if (me)
	{
		UStatusEffectComp* StatusEffectComp = me->FindComponentByClass<UStatusEffectComp>();
		if (StatusEffectComp && StatusEffectComp->IsBleeding( BodyPart ))
		{
			return ESlateVisibility::Visible;
		}
	}
	return ESlateVisibility::Hidden;
}

ESlateVisibility UHPWidget::GetBleedingVisibility() const
{
	APlayerBase* me = Cast<APlayerBase>( GetOwningPlayerPawn() );
	if (me)
	{
		UStatusEffectComp* StatusEffectComp = me->FindComponentByClass<UStatusEffectComp>();
		if (StatusEffectComp && StatusEffectComp->GetBleedingCount() > 0)
		{
			return ESlateVisibility::Visible;
		}
	}
	return ESlateVisibility::Hidden;
}

ESlateVisibility UHPWidget::GetFracturedVisibilityBodyPart( FName BodyPart ) const
{
	APlayerBase* me = Cast<APlayerBase>( GetOwningPlayerPawn() );
	if (me)
	{
		UStatusEffectComp* StatusEffectComp = me->FindComponentByClass<UStatusEffectComp>();
		if (StatusEffectComp && StatusEffectComp->IsFractured( BodyPart ))
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
		if (StatusEffectComp && StatusEffectComp->GetFractureCount() > 0)
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
		Color = Color.CopyWithNewOpacity( 0.5 );
		BodyPartImage->SetColorAndOpacity( Color );
	}
}

void UHPWidget::UpdateStatusText()
{
	APlayerBase* me = Cast<APlayerBase>( GetOwningPlayerPawn() );
	if (!me)
	{
		return;
	}
	UStatusEffectComp* StatusEffectComp = me->FindComponentByClass<UStatusEffectComp>();
	if (StatusEffectComp)
	{
		int32 BleedingCount = StatusEffectComp->GetBleedingCount();
		int32 FractureCount = StatusEffectComp->GetFractureCount();

		// 출혈 상태이상 부위가 있다면 텍스트를 업데이트합니다.
		if (BleedingCount > 0)
		{
			Bleeding_Text->SetText( FText::FromString( FString::Printf( TEXT( "%d" ) , BleedingCount ) ) );
			Bleeding_Text->SetVisibility( ESlateVisibility::Visible );
		}
		else
		{
			Bleeding_Text->SetVisibility( ESlateVisibility::Collapsed );
		}

		// 골절 상태이상 부위가 있다면 텍스트를 업데이트합니다.
		if (FractureCount > 0)
		{
			Fracture_Text->SetText( FText::FromString( FString::Printf( TEXT( "%d" ) , FractureCount ) ) );
			Fracture_Text->SetVisibility( ESlateVisibility::Visible );
		}
		else
		{
			Fracture_Text->SetVisibility( ESlateVisibility::Collapsed );
		}
	}

}

void UHPWidget::PlayHitAnim()
{
	PlayAnimation( HitAnimation );
}

void UHPWidget::UpdateStaminaBar()
{
	APlayerBase* me = Cast<APlayerBase>( GetOwningPlayerPawn() );
	if (me)
	{
		UStaminaComp* StaminaComp = me->FindComponentByClass<UStaminaComp>();
		if (StaminaComp && Stamina_Bar)
		{
			float StaminaPercent = StaminaComp->Stamina / StaminaComp->MaxStamina;
			Stamina_Bar->SetPercent( StaminaPercent );
		}
	}
}

void UHPWidget::StartCountdown( int32 CountdownTime )
{
	CurrentCountdownTime = CountdownTime;
	UpdateCountdown();

	// 타이머 시작, 1초마다 UpdateCountdown 호출
	GetWorld()->GetTimerManager().SetTimer( CountdownTimerHandle , this , &UHPWidget::UpdateCountdown , 1.0f , true );
}

void UHPWidget::StopCountdown()
{
	GetWorld()->GetTimerManager().ClearTimer( CountdownTimerHandle );
}

void UHPWidget::UpdateCountdown()
{
	if (CurrentCountdownTime >= 0)
	{
		if (ClearTimer_Text)
		{
			ClearTimer_Text->SetText( FText::AsNumber( CurrentCountdownTime ) );
		}
	
		if (CurrentCountdownTime == 0)
		{
			// 카운트다운이 끝나면 타이머 중지
			StopCountdown();
		}
		--CurrentCountdownTime;
	}
	
}

void UHPWidget::GameStartCountdown(int32 GameCountdownTime)
{
	GameCurrentCountdownTime = GameCountdownTime;
	UpdateGameCountdown();

	// 타이머 시작, 1초마다 UpdateCountdown 호출
	GetWorld()->GetTimerManager().SetTimer( GameCountdownTimerHandle , this , &UHPWidget::UpdateGameCountdown , 1.0f , true );
}

void UHPWidget::GameStopCountdown()
{
	GetWorld()->GetTimerManager().ClearTimer( GameCountdownTimerHandle );
}

void UHPWidget::UpdateGameCountdown()
{
	if (GameCurrentCountdownTime >= 0)
	{
		if (Timer_Text)
		{
			int32 Minutes = GameCurrentCountdownTime / 60;
			int32 Seconds = GameCurrentCountdownTime % 60;
			FString TimeText = FString::Printf( TEXT( "%02d:%02d" ) , Minutes , Seconds );
			Timer_Text->SetText( FText::FromString( TimeText ) );
		}
		if (GameCurrentCountdownTime == 0)
		{
			// 카운트다운이 끝나면 타이머 중지
			GameStopCountdown();

			APlayerBase* me = Cast<APlayerBase>( GetOwningPlayerPawn() );
			if (me && me->HealthComp)
			{
				me->HealthComp->bIsDead = true; // 플레이어 사망 처리 함수 호출

				ATarKOVPlayerController* pc = Cast<ATarKOVPlayerController>( me->GetController() );
				if (pc)
				{
					pc->CalculatePlayTime();
					pc->DisableInput( pc );
					me->OnDeath();
				}
			}
		}
		--GameCurrentCountdownTime;
	}

}

void UHPWidget::UpdateHPBarColor( UProgressBar* HPBar , float HPPercentage ) const
{
	FLinearColor Color;
	if (HPPercentage > 0.5f) // HP가 50% 이상일 때
	{
		Color = FLinearColor::Green;
	}
	else if (HPPercentage > 0.3f) // HP가 30%에서 50% 사이일 때
	{
		Color = FLinearColor::Yellow;
	}
	else // HP가 30% 이하일 때
	{
		Color = FLinearColor::Red;
	}

	if (HPBar)
	{
		HPBar->SetFillColorAndOpacity( Color );
	}
}

void UHPWidget::PlayEscapeAnim()
{
	PlayAnimation( EscapeAnimation );
}
