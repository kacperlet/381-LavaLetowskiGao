// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"


void UItemSlotWidget::SetQuantity(int32 Quantity) const
{
	ItemQuantityText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Quantity)));
}

void UItemSlotWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
    UpdateIcon();
}

void UItemSlotWidget::UpdateIcon()
{
	if (!ItemIconImage)
	{
		return;
	}
	
	const TCHAR* TexturePath;
	switch (ItemSlot)
	{
	case EItemSlot::Cushion:
		TexturePath = TEXT("/Game/Images/Cushion.Cushion");
		break;
	case EItemSlot::Extinguisher:
		TexturePath = TEXT("/Game/Images/FireExtinguisher.FireExtinguisher");
		break;
	default:
		return;
	}

	if (UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, TexturePath))
	{
		ItemIconImage->SetBrushFromTexture(Texture);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UItemSlotWidget: failed to load icon at %s"), TexturePath);
	}
}