// Fill out your copyright notice in the Description page of Project Settings.


#include "LSH/InventoryComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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
}

void UInventoryComponent::SetupInput( UEnhancedInputComponent* input )
{
	Super::SetupInput( input );

	if (nullptr == input) return;
	//Prone
	//input->BindAction( InventoryAction , ETriggerEvent::Started , this , &UInventoryComponent::InventoryOpen );
	input->BindAction( InventoryAction, ETriggerEvent::Started, this , &UInventoryComponent::InventoryOpen );
}