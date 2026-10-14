// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


bool UInventoryComponent::AddItem(EItemSlot Slot)
{
	// TODO: implement
	return false;
}

void UInventoryComponent::EquipSlot(EItemSlot Slot)
{
	// TODO: implement
}

void UInventoryComponent::ThrowEquipped()
{
	// TODO: implement
}

int32 UInventoryComponent::GetCount(EItemSlot Slot) const
{
	// TODO: implement
	return 0;
}

void UInventoryComponent::RefreshHeldActor()
{
	// TODO: implement
}
