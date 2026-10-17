#include "FireBarrier.h"

#include "LavaLetowskiGaoCharacter.h"

// Sets default values
AFireBarrier::AFireBarrier()
{
	PrimaryActorTick.bCanEverTick = false;

	Barrier = CreateDefaultSubobject<UBoxComponent>(TEXT("Barrier"));
	RootComponent = Barrier;
	Barrier->SetBoxExtent(FVector(100.f, 10.f, 200.f));
	Barrier->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	
	FireEffect = CreateDefaultSubobject<UNiagaraComponent>("FireEffect");
	FireEffect->SetupAttachment(Barrier);
	FireEffect->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AFireBarrier::BeginPlay()
{
	Super::BeginPlay();
	
	if (Barrier)
	{
		Barrier->OnComponentHit.AddDynamic(this, &AFireBarrier::OnHit);
	}
}

/** Push the player back after touching the fire */
void AFireBarrier::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ALavaLetowskiGaoCharacter* Character = Cast<ALavaLetowskiGaoCharacter>(OtherActor))
	{
		FVector CalculatedImpulse = Hit.ImpactNormal * -1000;
		
		Character->LaunchCharacter(FVector(CalculatedImpulse.X, CalculatedImpulse.Y, 500.f), false, false);
	}
}

/** Removes collisions and makes the fire go away */
void AFireBarrier::Disappear() const
{
	Barrier->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FireEffect->Deactivate();
}

