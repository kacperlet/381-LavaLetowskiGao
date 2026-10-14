// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	// Add item slots
	Slots.Add(EItemSlot::Cushion, {nullptr, 3, 1});
	Slots.Add(EItemSlot::Extinguisher, {nullptr, 3, 3});
}


bool UInventoryComponent::AddItem(EItemSlot Slot)
{
	FInventorySlot* selectedSlot = Slots.Find(Slot);
	if (selectedSlot && selectedSlot->Count < selectedSlot->Capacity)
	{
		selectedSlot->Count++;
		return true;
	}
	return false;
}

void UInventoryComponent::EquipSlot(EItemSlot Slot)
{
	EquippedSlot = Slot;
}

void UInventoryComponent::ThrowEquipped()
{
	FInventorySlot* Equipped = Slots.Find(EquippedSlot);
	if (Equipped->Count > 0)
	{
		// TODO: instantiate it and use the class
		
		Equipped->Count--;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No items left to throw!"));
	}
}

int32 UInventoryComponent::GetCount(EItemSlot Slot) const
{
	return Slots.Find(Slot)->Count;
}

void UInventoryComponent::RefreshHeldActor()
{
	// TODO: implement
}
