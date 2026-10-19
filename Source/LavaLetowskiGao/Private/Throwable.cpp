// Fill out your copyright notice in the Description page of Project Settings.

#include "Throwable.h"
#include "SprinklerTarget.h"
#include "LavaLetowskiGaoCharacter.h"

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
	
	Mesh->OnComponentHit.AddDynamic(this, &AThrowable::HandleHit);
	
	BaseScale = Mesh->GetComponentScale();
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
        ALavaLetowskiGaoCharacter* Carrier = Cast<ALavaLetowskiGaoCharacter>(GetOwner());
		if (!Carrier)
		{
			UE_LOG(LogTemp, Warning, TEXT("SetCarried: owner is not the character"));
			return;
		}

		// deactivate physics and collisions
        State = EThrowableState::Carried;
		Mesh->SetSimulatePhysics(false);
		Mesh->SetEnableGravity(false);
        Movement->StopMovementImmediately();
		Movement->Deactivate();
        Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		// make the mesh small so it looks correct in-hand
		const FVector OriginalScale = Mesh->GetComponentScale();
		Mesh->SetWorldScale3D(OriginalScale * InHandScale);
		
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
    	
    	// return scale
    	Mesh->SetWorldScale3D(BaseScale);
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
	
	GEngine->AddOnScreenDebugMessage(
		-1, 
		2.0f,
		FColor::Blue, 
		TEXT("Throwable hit surface!") 
	);
	
	if (ASprinklerTarget* Target = Cast<ASprinklerTarget>(OtherActor))
	{
		Target->HandleHit();
	}

    // disappear
    Destroy();
}

