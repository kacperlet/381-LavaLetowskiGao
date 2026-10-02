// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaGameMode.h"

ALavaGameMode::ALavaGameMode()
{
	// TODO: Implement
}

void ALavaGameMode::BeginPlay()
{
	// TODO: Implement
}

void ALavaGameMode::EndPlay(const EEndPlayReason::Type Reason)
{
	// TODO: Implement
}

float ALavaGameMode::GetTimeRemaining() const
{
	// TODO: Implement
	return 0.0f;
}

/** A key was picked up. The key itself does not know what that means. */
void ALavaGameMode::ReportKeyCollected()
{
	// TODO: Implement
}

/** The character touched lava. */
void ALavaGameMode::ReportLifeLost()
{
	// TODO: Implement
}

/** The player reached the hatch. The hatch does not check the keys itself. */
void ALavaGameMode::ReportHatchReached()
{
	// TODO: implement
}
