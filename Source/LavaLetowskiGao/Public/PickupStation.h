// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryComponent.h"   // for EItemSlot
#include "PickupStation.generated.h"

class UBoxComponent;

UCLASS()
class LAVALETOWSKIGAO_API APickupStation : public AActor
{
	GENERATED_BODY()

public:
	APickupStation();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
					   bool bFromSweep, const FHitResult& Sweep);

	void Restock();
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StationMesh;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	EItemSlot ItemType = EItemSlot::Cushion;

	UPROPERTY(EditAnywhere, Category = "Tuning", meta = (ClampMin = "0.0", Units = "s"))
	float RestockSeconds = 15.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> Trigger;

	bool bAvailable = true;
	FTimerHandle RestockTimer;
};
