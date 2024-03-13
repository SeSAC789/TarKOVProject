// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/PainPostProcess.h"

#include "Components/PostProcessComponent.h"

APainPostProcess::APainPostProcess()
{
    PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>( TEXT( "PainPostProcessComponent" ) );
    RootComponent = PostProcessComponent;

    InitializePostProcessComponent();
}

void APainPostProcess::EnablePainEffect(bool bEnable)
{
    PostProcessComponent->bEnabled = bEnable;

    // Settings 변수 대신 PostProcessComponent의 Settings 멤버에 직접 접근합니다.
    if (bEnable)
    {
        PostProcessComponent->Settings.bOverride_SceneFringeIntensity = true;
        PostProcessComponent->Settings.SceneFringeIntensity = 5.0f;
    }
    else
    {
        PostProcessComponent->Settings.bOverride_SceneFringeIntensity = false;
    }

    if (bEnable)
    {
        UE_LOG( LogTemp , Warning , TEXT( " APainPostProcess::EnablePainEffect, Pain Effect is enabled" ) );
    }
    else
    {
        UE_LOG( LogTemp , Warning , TEXT( "APainPostProcess::EnablePainEffectPain, Pain Effect is disabled" ) );
    }
}

void APainPostProcess::InitializePostProcessComponent()
{
    PostProcessComponent->Settings.bOverride_SceneFringeIntensity = false;
}

bool APainPostProcess::IsPainEffectActive() const
{
    return PostProcessComponent && PostProcessComponent->bEnabled;
}
