// Fill out your copyright notice in the Description page of Project Settings.


#include "Extinguisher.h"
#include "SprinklerTarget.h"
#include "InventoryComponent.h"
#include "Lava.h"

// override HandleHit from parent function
void AExtinguisher::HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Ignore hitting ourselves, our owner, or nothing -- same as in Throwable
	if (!OtherActor || OtherActor == this || OtherActor == GetOwner())
	{
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(
		-1, 
		2.0f,
		FColor::Blue, 
		TEXT("Extinguisher hit surface!") 
	);
	
	// if hit sprinkler, activate sprinkler and disappear
	if (ASprinklerTarget* Target = Cast<ASprinklerTarget>(OtherActor))
	{
		Target->HandleHit();
		Destroy();
		return;
	}
	
	// if hit lava, get destroyed
	if (ALava *Lava = Cast<ALava>(OtherActor))
	{
		Destroy();
		return;
	}

	// disappear anyway if anything else happens
	Destroy();
}