// Fill out your copyright notice in the Description page of Project Settings.

#include "Cushion.h"
#include "SprinklerTarget.h"
#include "InventoryComponent.h"
#include "Lava.h"

#include <ntstatus.h>

// override HandleHit from parent function
void ACushion::HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
		TEXT("Cushion hit surface!") 
	);
	
	// if hit lava, start 5 second timer until burning away (if we have time, add burning effect), become larger as a platform, disappear at the end of the timer
	if (ALava *Lava = Cast<ALava>(OtherActor))
	{
		// freeze at position on lava
		Mesh->SetSimulatePhysics(false);
		Movement->StopMovementImmediately();
		Movement->Deactivate();
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		
		// make the cushion grow
		const FVector OriginalScale = Mesh->GetComponentScale();
		Mesh->SetWorldScale3D(OriginalScale * PlatformScale);
		
		// destroy after 10 seconds
		if (!GetWorldTimerManager().IsTimerActive(BurnTimerHandle))
		{
			GetWorldTimerManager().SetTimer(
				BurnTimerHandle,
				this,
				&ACushion::BurnedAway,
				5.0f,
				false
			);
		}
		return;
	}

	// disappear anyway if anything else happens
	Destroy();
}

void ACushion::BurnedAway()
{
	// can add a burned away animation here
	Destroy();
}
