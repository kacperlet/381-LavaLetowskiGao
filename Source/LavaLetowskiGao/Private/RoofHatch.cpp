// Fill out your copyright notice in the Description page of Project Settings.


#include "RoofHatch.h"
#include "LavaGameMode.h"

// Sets default values
ARoofHatch::ARoofHatch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARoofHatch::BeginPlay()
{
	Super::BeginPlay();
	
	if (UBoxComponent* Box = FindComponentByClass<UBoxComponent>())
	{
		Box->OnComponentBeginOverlap.AddDynamic(this, &ARoofHatch::HandleOverlap);
	}
	
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + FVector(1100.f, 0.f, 0.f); // move up 400 cm
}

// Called every frame
void ARoofHatch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bOpening)
	{
		FVector NewLoc = FMath::VInterpTo(GetActorLocation(), EndLocation, DeltaTime, 2.f);
		SetActorLocation(NewLoc);

		if (NewLoc.Equals(EndLocation, 1.f))
		{
			SetActorLocation(EndLocation);
			bOpening = false;
			
			// make sure widget can not be opened anymore
			Destroy();
			return;
		}
	}
}

void ARoofHatch::OpenHatch()
{
	bOpening = true;
}

void ARoofHatch::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn != nullptr && Pawn->IsPlayerControlled())
	{
		GEngine->AddOnScreenDebugMessage(
			3,
			2.0f,
			FColor::Green, 
			TEXT("Arrived at hatch")        
		);
		
		if (ALavaGameMode* Gm = GetWorld()->GetAuthGameMode<ALavaGameMode>())
		{
			// report hatch reached
			Gm->ReportHatchReached();
		}
	}
}

