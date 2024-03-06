// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGrid_Widget.generated.h"

/**
 * 
 */
UCLASS()
class TARKOVPROJECT_API UInventoryGrid_Widget : public UUserWidget
{
	GENERATED_BODY()

private:

	class UInventoryComponent* inventoryComponent;



public:

	/// 
	/// @param inventoryComponent1 
	/// @param tileSize 타일의 크기
	UFUNCTION()
	void Initializee(class UInventoryComponent* InventoryComponent1 , float tileSize1);

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = Private )
	float tileSize;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UBorder* GridBorder;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UGridCanvasPanel* GridCanvasPanel;
};
