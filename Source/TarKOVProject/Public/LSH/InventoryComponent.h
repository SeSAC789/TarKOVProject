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

	///플레이어컨트롤러 찾기
	virtual APlayerController* GetPlayerController();

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


	UPROPERTY(EditDefaultsOnly)
	class ALSHTestPlayer* player;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UInvnetoryWidget> InventoryWidgetFactory;//인벤토리 위젯 만들기

	UPROPERTY()
	class UInvnetoryWidget* inventoryWidget;//생성된 인벤토리 위젯 포인터

	UPROPERTY(BlueprintReadOnly,EditInstanceOnly,meta=(ExposeOnSpawn="true"),Category=Constants)
	int32 Columns;//인벤토리 창의 열

	UPROPERTY( BlueprintReadOnly , EditInstanceOnly , meta = (ExposeOnSpawn = "true") , Category = Constants )
	int32 Rows;//인벤토리 창의 행
};
