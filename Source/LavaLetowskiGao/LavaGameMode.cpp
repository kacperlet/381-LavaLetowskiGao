// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaGameMode.h"

#include "LavaHUD.h"
#include "LavaLetowskiGaoPlayerController.h"
#include "MenuHUD.h"
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
	
	// add result widget class
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetAssetFinder(TEXT("/Game/User_Interface/BP_ResultWidget"));
	if (WidgetAssetFinder.Succeeded())
	{
		ResultWidgetClass = WidgetAssetFinder.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CRITICAL: Could not find the ResultWidget asset at the specified path"));
	}
}

void ALavaGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	
	// after start make sure that player input can be read
	if (PC)
	{
		// hide mouse cursor
		PC->SetShowMouseCursor(false);
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
        // set viewport as focus
		FSlateApplication::Get().SetAllUserFocusToGameViewport();
	}
	
	GEngine->AddOnScreenDebugMessage(
			1,
			2.0f,
			FColor::Blue, 
			TEXT("Timer Started")        
	);
	
	// FOR TESTING ONLY -- SHORT TIMER
	LevelSeconds = 30.f;
	
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
			1,
			2.0f,
			FColor::Green, 
			TimeMessage        
		);
		
	}
	else
	{
		EndGame(false, TEXT("Ran out of time D:"));
		
		GEngine->AddOnScreenDebugMessage(
			1,
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
	LivesLeft--;
	if (LivesLeft <= 0 && !IsGameOver)
	{
		EndGame(false, TEXT("Ran out of lives :C"));
	}
}

/** The player reached the hatch. The hatch does not check the keys itself. */
void ALavaGameMode::ReportHatchReached()
{
	// TODO: Implement
}

int32 ALavaGameMode::GetRiseHeight() const
{
	if (Lava == nullptr)
		return 0;
	
	return FMath::RoundToInt(Lava->GetRiseHeight());
}

void ALavaGameMode::EndGame(bool bWon, FString Reason)
{
	if (bWon)
	{
		// TODO:
	}
	else
	{
		// show result screen
		if (const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0)) // need to set the player who gets the screen
		{
			if (ALavaHUD* LavaHUD = Cast<ALavaHUD>(PC->GetHUD()))
			{
				// call the show result screen
				const FText DeathMessage = FText::FromString(Reason);
				LavaHUD->ShowResultScreen(ResultWidgetClass, DeathMessage);
			}
		}
	}
	
	GetWorldTimerManager().ClearTimer(LevelTimer); // stop timer
	IsGameOver = true;
}
