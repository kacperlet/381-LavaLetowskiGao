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
	
	// switch slot
	EquippedSlot = Slot;
	
	if (EquippedSlot == EItemSlot::None)
	{ 
		return;
	}
	
	if (GetCount(EquippedSlot) > 0)
	{
		// get item class
		FInventorySlot* SlotData;
		if (EquippedSlot == EItemSlot::Cushion)
		{
			SlotData = Slots.Find(EItemSlot::Cushion);
			if (!SlotData || !SlotData->ItemClass) { return; }
		}
		else if (EquippedSlot == EItemSlot::Extinguisher)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Is Extinguisher"));
			SlotData = Slots.Find(EItemSlot::Extinguisher);
			if (!SlotData || !SlotData->ItemClass) { return; }
		}
		else
		{
			// error
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Other"));
			return;
		}
		
		// get owner
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		if (!PC) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Owner is not a PlayerController")); return; }
		ALavaLetowskiGaoCharacter* Character = PC ? Cast<ALavaLetowskiGaoCharacter>(PC->GetPawn()) : nullptr;
		if (!Character) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pawn is not LavaLetowskiGaoCharacter")); return; }
		
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
		
		// carry item
		if (!HeldActor) return;
		HeldActor->SetCarried(true);
	}
	else{
		// get owner
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		if (!PC) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Owner is not a PlayerController")); return; }
		ALavaLetowskiGaoCharacter* Character = PC ? Cast<ALavaLetowskiGaoCharacter>(PC->GetPawn()) : nullptr;
		if (!Character) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pawn is not LavaLetowskiGaoCharacter")); return; }
		
		// remove crosshair
		Character->SetCrosshairVisible(false);
	}
}

void UInventoryComponent::ThrowEquipped()
{
	if (!HeldActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HeldActor is NULL"));
		return;
	}
	FInventorySlot* Equipped = Slots.Find(EquippedSlot);
	if (Equipped->Count > 0)
	{
		Equipped->Count--;

		// get owner
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		if (!PC) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Owner is not a PlayerController")); return; }
		ALavaLetowskiGaoCharacter* Character = PC ? Cast<ALavaLetowskiGaoCharacter>(PC->GetPawn()) : nullptr;
		if (!Character) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pawn is not LavaLetowskiGaoCharacter")); return; }
		
		HeldActor->Throw(Character->GetControlRotation().Vector());
		HeldActor = nullptr;
		
		// make sure to handle when there are still items of the same type available to throw
		EquipSlot(EquippedSlot);
	}
	else
	{
		// get owner
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		if (!PC) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Owner is not a PlayerController")); return; }
		ALavaLetowskiGaoCharacter* Character = PC ? Cast<ALavaLetowskiGaoCharacter>(PC->GetPawn()) : nullptr;
		if (!Character) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pawn is not LavaLetowskiGaoCharacter")); return; }
		Character->SetCrosshairVisible(false);
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
