// Fill out your copyright notice in the Description page of Project Settings.

#include "LavaKey.h"
#include "LavaGameMode.h"

// Sets default values
ALavaKey::ALavaKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALavaKey::BeginPlay()
{
	Super::BeginPlay();
	
	// Store the starting location of the actor
	InitialLocation = GetActorLocation();
	
	if (UPrimitiveComponent* PrimitiveComp = FindComponentByClass<UPrimitiveComponent>()) // find our collision circle
	{
		// bind HandleOverlap
		PrimitiveComp->OnComponentBeginOverlap.AddDynamic(this, &ALavaKey::HandleOverlap);
	}
}

// Called every frame
void ALavaKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// rotate key
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += SpinRate * DeltaTime; 
	
	// let key bob up and down
	FVector CurrentLocation = GetActorLocation();
	float WorldTime = GetWorld()->GetTimeSeconds();
	float NewZValue = InitialLocation.Z + (FMath::Sin(WorldTime * BobSpeed) * BobAmplitude);
	CurrentLocation.Z = NewZValue;
	
	// apply movement -- set bSweep to true so movement is smooth
	SetActorLocationAndRotation(CurrentLocation, CurrentRotation, true);
}

void ALavaKey::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn != nullptr && Pawn->IsPlayerControlled())
	{
		GEngine->AddOnScreenDebugMessage(
			3,
			2.0f,
			FColor::Green, 
			TEXT("Key collected")        
		);
		
		if (ALavaGameMode* Gm = GetWorld()->GetAuthGameMode<ALavaGameMode>())
		{
			// increment number of keys collected
			Gm->ReportKeyCollected();
			
			// Remove the key from the world
			Destroy();
		}
	}
}
