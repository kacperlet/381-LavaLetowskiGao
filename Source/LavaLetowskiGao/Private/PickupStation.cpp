// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupStation.h"
#include "LavaLetowskiGaoCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
APickupStation::APickupStation()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;

	Trigger->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	Trigger->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	Trigger->SetGenerateOverlapEvents(true);
	
	StationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StationMesh"));
	StationMesh->SetupAttachment(Trigger);
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));
	ItemMesh->SetupAttachment(Trigger);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void APickupStation::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APickupStation::HandleOverlap);
	ItemMesh->SetVisibility(true);
}

void APickupStation::EndPlay(const EEndPlayReason::Type Reason)
{
	// cleanup timer, if left over
	GetWorldTimerManager().ClearTimer(RestockTimer);
	Super::EndPlay(Reason);
}

void APickupStation::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	if (!bAvailable)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Item not available!"));
		return;
	}
	
	// on overlap with character
	if (ALavaLetowskiGaoCharacter* Player = Cast<ALavaLetowskiGaoCharacter>(OtherActor))
	{
		AController* PC = Player->GetController();
		if (!PC) return;
		if (UInventoryComponent* Inv = PC->FindComponentByClass<UInventoryComponent>())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inventory Component Found"));
			if (!(Inv->AddItem(ItemType)))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to add item to Inventory!"));
				return;
			}
		}
		
		// hide item
		ItemMesh->SetVisibility(false);
		
		// set not available
		bAvailable = false;
		
		if (!GetWorldTimerManager().IsTimerActive(RestockTimer))
		{
			GetWorldTimerManager().SetTimer(
				RestockTimer,
				this,
				&APickupStation::Restock,
				RestockSeconds,
				false
			);
		}
	}
}

void APickupStation::Restock()
{
	// set available
	bAvailable = true;
	
	// show item again
	ItemMesh->SetVisibility(true);
}

