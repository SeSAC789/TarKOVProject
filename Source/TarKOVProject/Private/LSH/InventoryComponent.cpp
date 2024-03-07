// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH/InventoryComponent.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LSH/LSHTestPlayer.h"
#include "LSH/InvnetoryWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	player = Cast<ALSHTestPlayer>( GetOwner() );
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	inventoryWidget = Cast<UInvnetoryWidget>( CreateWidget( GetPlayerController(), InventoryWidgetFactory ) );//인벤토리 위젯 생성
}

APlayerController* UInventoryComponent::GetPlayerController()
{
	return Cast<APlayerController>( player->GetController() );
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::InventoryOpen( const FInputActionValue& Value )
{
	UE_LOG( LogTemp , Warning , TEXT( "Inventory Open" ) );
	if(inventoryWidget->IsInViewport())//인벤 끄기
	{
		inventoryWidget->RemoveFromParent();
		UWidgetBlueprintLibrary::SetInputMode_GameOnly( GetPlayerController() );
		GetPlayerController()->bShowMouseCursor = false;
	}
	else//인벤켜기
	{
		inventoryWidget->AddToViewport();
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(GetPlayerController(),inventoryWidget,EMouseLockMode::DoNotLock,false);
		GetPlayerController()->bShowMouseCursor = true;
	}
}

void UInventoryComponent::SetupInput( UEnhancedInputComponent* input )
{
	Super::SetupInput( input );

	if (nullptr == input) return;
	//Prone
	//input->BindAction( InventoryAction , ETriggerEvent::Started , this , &UInventoryComponent::InventoryOpen );
	input->BindAction( InventoryAction, ETriggerEvent::Started, this , &UInventoryComponent::InventoryOpen );
}