// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerBaseComp.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TARKOVPROJECT_API UInventoryComponent : public UPlayerBaseComp
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//FORCEINLINE virtual void SetupInput( class UEnhancedInputComponent* input )
	//{
	//}
	virtual void SetupInput( UEnhancedInputComponent* input );
	
	/** Inventory Input Action */
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	class UInputAction* InventoryAction;

	void InventoryOpen( const FInputActionValue& Value );

};
