// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaGameMode.h"

#include "LavaLetowskiGaoPlayerController.h"
#include "MenuHUD.h"

ALavaGameMode::ALavaGameMode()
{
	//
	
	// add player controller class
	PlayerControllerClass = ALavaLetowskiGaoPlayerController::StaticClass();
	// add hud class
	HUDClass = AMenuHUD::StaticClass();
}

void ALavaGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Blue, 
			TEXT("Timer Started")        
	);
	
	// Start timer
	GetWorldTimerManager().SetTimer(LevelTimer, this, &ALavaGameMode::UpdateCountdown, 1.0f, true);
}

void ALavaGameMode::UpdateCountdown()
{
	if (LevelSeconds > 0.0f)
	{
		LevelSeconds -= 1;
		
		FString TimeMessage = FString::Printf(TEXT("Current Time: %f"), LevelSeconds);
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Green, 
			TimeMessage        
		);
		
	}
	else
	{
		GetWorldTimerManager().ClearTimer(LevelTimer); // stop timer
		
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Blue, 
			TEXT("Timer Ended")        
	);
		// TODO: end game
	}
}

void ALavaGameMode::EndPlay(const EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);
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
