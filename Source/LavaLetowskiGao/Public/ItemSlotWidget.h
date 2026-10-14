// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class LAVALETOWSKIGAO_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// determines the icon that is shown
	UPROPERTY(EditAnywhere, Category = "Appearance")
	EItemSlot ItemSlot = EItemSlot::Cushion;
	
	void SetQuantity(int32 Quantity) const;

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* ItemQuantityText;
	UPROPERTY(meta = (BindWidget)) UImage* ItemIconImage;
	
	virtual void NativePreConstruct() override;
	
	void UpdateIcon();
};
