// Fill out your copyright notice in the Description page of Project Settings.


#include "Throwable.h"

// Sets default values
AThrowable::AThrowable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThrowable::BeginPlay()
{
	Super::BeginPlay();
	
}


void AThrowable::Throw(const FVector& Direction)
{
	// TODO: implement
}

void AThrowable::SetCarried(bool bCarried)
{
	// TODO: implement
}

void AThrowable::HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// TODO: implement
}

