//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Slate/SlateBrushAsset.h"
//#include "ColorSlateBrushAsset.generated.h"
//
///**
// * 
// */
//UCLASS()
//class TARKOVPROJECT_API UColorSlateBrushAsset : public USlateBrushAsset
//{
//	GENERATED_BODY()
//	
//};

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Slate/SlateBrushAsset.h"
#include "ColorSlateBrushAsset.generated.h"

UCLASS()
class TARKOVPROJECT_API UColorSlateBrushAsset : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Brush" )
    FSlateBrush Brush;
};