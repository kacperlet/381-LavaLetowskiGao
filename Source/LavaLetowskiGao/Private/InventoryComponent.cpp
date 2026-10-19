// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Cushion.h"
#include "LavaLetowskiGaoCharacter.h"

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
	// clear whatever is currently in hand
	RefreshHeldActor();
	
	EquippedSlot = Slot;
	
	if (GetCount(EquippedSlot) > 0)
	{
		if (EquippedSlot == EItemSlot::Cushion)
		{
			// get item class
			FInventorySlot* SlotData = Slots.Find(EItemSlot::Cushion);
			if (!SlotData || !SlotData->ItemClass) return;

			// get owner
			ACharacter* Character = Cast<ACharacter>(GetOwner());
			if (!Character) return;

			// hand information to our cushion
			FActorSpawnParameters Params;
			Params.Owner = Character;
			Params.Instigator = Character;
			Params.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// spawn item
			AThrowable* Spawned = GetWorld()->SpawnActor<AThrowable>(
				SlotData->ItemClass,
				Character->GetActorLocation(),
				Character->GetActorRotation(),
				Params);

			// carry cushion
			if (ACushion* Cushion = Cast<ACushion>(Spawned))
			{
				Cushion->SetCarried(true);
			}
			
			// carry fire extinguisher
			// if (AExtinguisher* Extinguisher = Cast<AExtinguisher>(Spawned))
			// {
			// 	Extinguisher->SetCarried(true);
			// }
		}
	}
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

EItemSlot UInventoryComponent::GetEquipped() const
{
	return EquippedSlot;
}

void UInventoryComponent::RefreshHeldActor()
{
	if (HeldActor != nullptr)
	{
		HeldActor->Destroy();
		HeldActor = nullptr;
	}
}
