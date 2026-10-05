// Lava.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lava.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class LAVALETOWSKIGAO_API ALava : public AActor
{
	GENERATED_BODY()

public:
	ALava();

	virtual void Tick(float DeltaTime) override;

	/** How far the surface has risen since the game started. Drives the HUD. */
	UFUNCTION(BlueprintPure, Category = "Lava")
	float GetRiseHeight() const;
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
	void SetLavaSpeed(float Speed);
protected:
	virtual void BeginPlay() override;
	// The signature must match FComponentBeginOverlapSignature exactly,
	// and it must be marked UFUNCTION, or it will silently never be called.
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
					   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
					   bool bFromSweep, const FHitResult& Sweep);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Surface;

	/** Sits just under the surface. This is what actually detects the player. */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> Volume;

	UPROPERTY(EditAnywhere, Category = "Tuning", meta = (ClampMin = "0.0", Units = "cm/s"))
	float RiseRate = 40.f;
	
	UPROPERTY(EditAnywhere, Category = "Tuning", meta = (ClampMin = "0.0", Units = "cm"))
	float SurfaceLength = 1000.f;
	
	UPROPERTY(EditAnywhere, Category = "Tuning", meta = (ClampMin = "0.0", Units = "cm"))
	float SurfaceZOffset = 110.f; // How much the surface is offset from the bounding volume

	/** Recorded at BeginPlay so GetRiseHeight has something to measure from. */
	float StartZ = 0.f;
	
	/** Used to prevent collisions being applied twice */
	bool DamageImmunity = false; 
	FTimerHandle ImmunityTimer;
	
	void UnFreeze();
};