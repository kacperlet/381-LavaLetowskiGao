#include "FireBarrier.h"

// Sets default values
AFireBarrier::AFireBarrier()
{
	PrimaryActorTick.bCanEverTick = false;

	Barrier = CreateDefaultSubobject<UBoxComponent>(TEXT("Barrier"));
	RootComponent = Barrier;
	Barrier->SetBoxExtent(FVector(100.f, 10.f, 200.f));
	Barrier->SetCollisionProfileName(TEXT("BlockAll"));
	
	FireEffect = CreateDefaultSubobject<UNiagaraComponent>("FireEffect");
	FireEffect->SetupAttachment(Barrier);
	FireEffect->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AFireBarrier::BeginPlay()
{
	Super::BeginPlay();
	
}

/** Removes collisions and makes the fire go away */
void AFireBarrier::Disappear() const
{
	Barrier->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FireEffect->Deactivate();
}

