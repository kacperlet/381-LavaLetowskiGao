// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sprinkler.h"
#include "GameFramework/Actor.h"
#include "SprinklerTarget.generated.h"

UCLASS()
class LAVALETOWSKIGAO_API ASprinklerTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprinklerTarget();
	
	// Called by throwable on hit
	void HandleHit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterialInterface* Material;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterialInterface* HitMaterial;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Config")
	TObjectPtr<ASprinkler> Sprinkler;
	
	bool WasHit = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
