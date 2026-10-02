// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaGameMode.h"

#include "LavaHUD.h"
#include "LavaLetowskiGaoPlayerController.h"
#include "MenuHUD.h"

// (may be optional)
#include "Kismet/GameplayStatics.h"

ALavaGameMode::ALavaGameMode()
{
	// add third person controller
	static ConstructorHelpers::FClassFinder<APlayerController> PCClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonPlayerController"));
	if (PCClass.Class != nullptr)
	{
		PlayerControllerClass = PCClass.Class;
	}
	
	// add third person character
	static ConstructorHelpers::FClassFinder<APawn> PawnBPClass(
		TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PawnBPClass.Class;
	}
	
	// add hud class to game-mode
	HUDClass = ALavaHUD::StaticClass();
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
		// show result screen
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0); // need to set the player who gets the screen
		if (PC)
		{
			ALavaHUD* LavaHUD = Cast<ALavaHUD>(PC->GetHUD());
			if (LavaHUD)
			{
				// call the function
				LavaHUD->ShowResultScreen();
			}
		}
		
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
	return LevelSeconds;
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
