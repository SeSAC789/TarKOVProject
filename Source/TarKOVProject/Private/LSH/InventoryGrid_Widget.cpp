// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH/InventoryGrid_Widget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"

void UInventoryGrid_Widget::Initializee(UInventoryComponent* inventoryComponent1, float tileSize1)
{
	inventoryComponent = inventoryComponent1;
	auto slot = UWidgetLayoutLibrary::SlotAsCanvasSlot( GridBorder );
	//slot->SetSize()

	
}
