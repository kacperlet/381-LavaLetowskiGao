// Fill out your copyright notice in the Description page of Project Settings.


#include "Throwable.h"

// Sets default values
AThrowable::AThrowable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetMobility(EComponentMobility::Movable);
    Mesh->SetSimulatePhysics(false);  
	
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	
	Movement->bAutoActivate = false;

	Movement->ProjectileGravityScale = 0.f;
	Movement->InitialSpeed = 0;
	Movement->MaxSpeed = 0;

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AThrowable::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThrowable::Throw(const FVector& Direction)
{
	SetCarried(false);
    State = EThrowableState::Thrown;

    if (AActor* Thrower = GetOwner())
    {
        Mesh->IgnoreActorWhenMoving(Thrower, true);
    }

	Movement->SetUpdatedComponent(Mesh);

	Movement->ProjectileGravityScale = 1.f;

    Movement->Activate(true);
    Movement->Velocity = Direction.GetSafeNormal() * ThrowSpeed;

	UE_LOG(LogTemp, Warning, TEXT("THROW2 updated=%s vel=%s"),
    *GetNameSafe(Movement->UpdatedComponent), *Movement->Velocity.ToString());
}

void AThrowable::SetCarried(bool bCarried)
{
	if (bCarried)
    {
		UE_LOG(LogTemp, Warning, TEXT("SetCarried Mesh=%s Movement=%s"),
    		*GetNameSafe(Mesh), *GetNameSafe(Movement));
        ALavaLetowskiGaoCharacter* Carrier = Cast<ALavaLetowskiGaoCharacter>(GetOwner());
        if (!Carrier) return;

        State = EThrowableState::Carried;
		Mesh->SetSimulatePhysics(false);
		Mesh->SetEnableGravity(false);
        Movement->Deactivate();
        Movement->StopMovementImmediately();
        Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        AttachToComponent(Carrier->GetMesh(),
            FAttachmentTransformRules::SnapToTargetNotIncludingScale,
            TEXT("hand_r"));
    }
    else
    {
        if (State != EThrowableState::Carried) return;
        DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        State = EThrowableState::Idle;
		Mesh->SetEnableGravity(true);
    }
}

void AThrowable::HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// bare minimum so children classes can override

	// Ignore hitting ourselves, our owner, or nothing
    if (!OtherActor || OtherActor == this || OtherActor == GetOwner())
    {
        return;
    }

    // disappear
    Destroy();
}

