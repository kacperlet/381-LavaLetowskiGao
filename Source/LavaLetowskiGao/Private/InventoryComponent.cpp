// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Cushion.h"
#include "Extinguisher.h"
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Adding Item!"));
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Equip Slot"));
	// clear whatever is currently in hand
	RefreshHeldActor();
	
	// switch slot
	EquippedSlot = Slot;
	
	if (GetCount(EquippedSlot) > 0)
	{
		// get item class
		FInventorySlot* SlotData;
		if (EquippedSlot == EItemSlot::Cushion)
		{
			SlotData = Slots.Find(EItemSlot::Cushion);
			if (!SlotData || !SlotData->ItemClass) return;
		}
		else if (EquippedSlot == EItemSlot::Extinguisher)
		{
			SlotData = Slots.Find(EItemSlot::Extinguisher);
			if (!SlotData || !SlotData->ItemClass) return;
		}
		else
		{
			// error
			return;
		}
		
		// get owner
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		ALavaLetowskiGaoCharacter* Character = PC ? Cast<ALavaLetowskiGaoCharacter>(PC->GetPawn()) : nullptr;
		if (!Character) return;
		
		// put crosshair
		Character->SetCrosshairVisible(true);
		
		// hand information to our item
		FActorSpawnParameters Params;
		Params.Owner = Character;
		Params.Instigator = Character;
		Params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// spawn item
		HeldActor = GetWorld()->SpawnActor<AThrowable>(
			SlotData->ItemClass,
			Character->GetActorLocation(),
			Character->GetActorRotation(),
			Params);
		
		// carry cushion
		if (ACushion* Cushion = Cast<ACushion>(HeldActor))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Equipped Cushion"));
			Cushion->SetCarried(true);
		}
		
		//carry fire extinguisher
		if (AExtinguisher* Extinguisher = Cast<AExtinguisher>(HeldActor))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Equipped Extinguisher"));
			Extinguisher->SetCarried(true);
		}
	}
}

void UInventoryComponent::ThrowEquipped()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Throw Equipped!"));
	FInventorySlot* Equipped = Slots.Find(EquippedSlot);
	if (Equipped->Count > 0)
	{		
		Equipped->Count--;
		
		// get owner
		ALavaLetowskiGaoCharacter* Character = Cast<ALavaLetowskiGaoCharacter>(GetOwner());
		if (!Character) return;
		
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Throw Item!"));
		HeldActor->Throw(Character->GetControlRotation().Vector());
		
		// make sure to handle when there are still items of the same type available to throw
		EquipSlot(EquippedSlot);
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
