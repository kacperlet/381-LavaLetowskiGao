// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
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
	
	UPROPERTY(EditAnywhere, Category = "Appearance")
	FLinearColor UnSelectedColor = FLinearColor(0.088f, 0.088f, 0.088f, 0.5f);
	
	UPROPERTY(EditAnywhere, Category = "Appearance")
	FLinearColor SelectedColor = FLinearColor(0.095f, 0.095f, 0.095f, 0.8f);
	
	void SetQuantity(int32 Quantity) const;
	
	void SetIsSelected(bool bIsSelected) const;

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* ItemQuantityText;
	UPROPERTY(meta = (BindWidget)) UImage* ItemIconImage;
	UPROPERTY(meta = (BindWidget)) UBorder* Border;
	
	virtual void NativePreConstruct() override;
	
	void UpdateIcon();
};
