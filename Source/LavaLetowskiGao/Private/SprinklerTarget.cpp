// Fill out your copyright notice in the Description page of Project Settings.


#include "SprinklerTarget.h"

// Sets default values
ASprinklerTarget::ASprinklerTarget()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh"));
	RootComponent = Mesh;
	
	// Get material assets
	ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/Materials/M_Target.M_Target"));
	if (MaterialAsset.Succeeded())
	{
		Material = MaterialAsset.Object;
	}
	
	ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialHitAsset(TEXT("/Game/Materials/M_TargetHit.M_TargetHit"));
	if (MaterialHitAsset.Succeeded())
	{
		HitMaterial = MaterialHitAsset.Object;
	}
}

// Called when the game starts or when spawned
void ASprinklerTarget::BeginPlay()
{
	Super::BeginPlay();
	
	if (Material)
	{
		Mesh->SetMaterial(0, Material);
	}
}

// Called every frame
void ASprinklerTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprinklerTarget::HandleHit()
{
	if (!WasHit)
	{
		WasHit = true;
		
		GEngine->AddOnScreenDebugMessage(
			-1, 
			2.0f,
			FColor::Blue, 
			TEXT("Target was hit") 
		);
		
		// update material
		if (HitMaterial)
		{
			Mesh->SetMaterial(0, HitMaterial);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(
			-1, 
			2.0f,
			FColor::Blue, 
			TEXT("Material Failed") 
			);
		}
		
		// turn on water sprinkler effect
		if (Sprinkler)
		{
			Sprinkler->StartSprinkler();
		}
		
		// remove fire barriers
		for (const AFireBarrier* Fire : FireBarriers)
		{
			Fire->Disappear();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(
		-1, 
		2.0f,
		FColor::Blue, 
		TEXT("Target was already hit") 
	);
	}
}
