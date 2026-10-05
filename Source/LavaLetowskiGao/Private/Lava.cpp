// Fill out your copyright notice in the Description page of Project Settings.


#include "Lava.h"

#include "LavaGameMode.h"
#include "LavaLetowskiGaoCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ALava::ALava()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Surface = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Surface"));
	check(Surface != nullptr);
	
	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	check(Volume != nullptr);
	
	// attach surface to collision volume
	RootComponent = Volume;
	Surface->SetupAttachment(Volume);
	
	Volume->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // non-blocking collision
	Volume->SetGenerateOverlapEvents(true);
	Surface->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ALava::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	Volume->SetBoxExtent(FVector(SurfaceLength, SurfaceLength, 100.f));
	Surface->SetRelativeLocation(FVector(0.f, 0.f, SurfaceZOffset));
}

// Called when the game starts or when spawned
void ALava::BeginPlay()
{
	Super::BeginPlay();
	
	if (Volume)
	{
		StartZ = Volume->GetComponentLocation().Z;
		
		if (!Volume->OnComponentBeginOverlap.IsAlreadyBound(this, &ALava::HandleOverlap))
		{
			Volume->OnComponentBeginOverlap.AddDynamic(this, &ALava::HandleOverlap);
		}
	}

	// add lava to game-mode for easier access
	if (ALavaGameMode* Gm = GetWorld()->GetAuthGameMode<ALavaGameMode>())
	{
		Gm->RegisterLava(this);
	}
}

// Called every frame
void ALava::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddActorWorldOffset(FVector(0, 0, RiseRate * DeltaTime));
}

void ALava::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn != nullptr && Pawn->IsPlayerControlled() && !DamageImmunity)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.0f,
			FColor::Red, 
			TEXT("Lava collision")        
		);
		
		if (ALavaGameMode* Gm = GetWorld()->GetAuthGameMode<ALavaGameMode>())
		{
			DamageImmunity = true;
			
			// Move Lava Down
			AddActorWorldOffset(FVector(0, 0, -500));
			
			// Teleport player to last safe location
			Cast<ALavaLetowskiGaoCharacter>(Pawn)->TeleportToLastSafeLocation();
			
			// decrease number of lives
			Gm->ReportLifeLost();
			Gm->IsPlayerInjured = true;
			
			GetWorldTimerManager().SetTimer(ImmunityTimer, [this]() { DamageImmunity = false; GetWorld()->GetAuthGameMode<ALavaGameMode>()->IsPlayerInjured = false;}, 0.5f, false);
		}
	}
}

float ALava::GetRiseHeight() const
{
	return Volume->GetComponentLocation().Z - StartZ;
}

