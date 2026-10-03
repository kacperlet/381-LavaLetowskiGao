// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaKey.h"

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
	
}

// Called every frame
void ALavaKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALavaKey::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	// TODO: Implement
}
