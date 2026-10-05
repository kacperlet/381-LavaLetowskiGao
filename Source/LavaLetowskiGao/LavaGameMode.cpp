// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaGameMode.h"

#include "LavaHUD.h"
#include "LavaLetowskiGaoPlayerController.h"
#include "MenuHUD.h"
#include "RoofHatch.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	KeysCollected++;
	
	// earn 200 points per key
	Score += 200;
}

/** The character touched lava. */
void ALavaGameMode::ReportLifeLost()
{
	LivesLeft--;
	
	// lose 100 points per life lost
	Score -= 100;
	
	if (LivesLeft <= 0 && !IsGameOver)
	{
		EndGame(false, TEXT("Ran out of lives :C"));
	}
}

void ALavaGameMode::ReportHatchSubmerged()
{
	EndGame(false, TEXT("The hatch has been submerged :<"));
}

/** The player reached the hatch. The hatch does not check the keys itself. */
void ALavaGameMode::ReportHatchReached()
{
	
	if (GetKeysCollected() >= 3)
	{
		// open/destroy the hatch
		if (ARoofHatch* Hatch = Cast<ARoofHatch>(UGameplayStatics::GetActorOfClass(this, ARoofHatch::StaticClass())))
		{
			Hatch->OpenHatch();
		}
		
		// end the game when the player arrives on the roof
		EndGame(true, TEXT(""));
	}
}

int32 ALavaGameMode::GetRiseHeight() const
{
	if (Lava == nullptr)
		return 0;
	
	return FMath::RoundToInt(Lava->GetRiseHeight());
}

void ALavaGameMode::EndGame(bool bWon, FString Reason)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;
	
	// stop player movement if game lost
	if (!bWon)
	{
		// stop existing movement
		if (ACharacter* Char = PC->GetCharacter())
		{
			UCharacterMovementComponent* Move = Char->GetCharacterMovement();
			Move->StopMovementImmediately();
			Move->DisableMovement();
		}
	}
	
	// stop the lava
	Lava->Destroy();
	
	// determine death message
	// empty death message means win
	FText DeathMessage = FText::GetEmpty();
	if (bWon)
	{
		// if won, add points to score for every second left on the clock
		Score += static_cast<int>(GetTimeRemaining());
	}
	else
	{
		// if lost, set a death message
		DeathMessage = FText::FromString(Reason);
	}
	
	// show result screen
	if (ALavaHUD* LavaHUD = Cast<ALavaHUD>(PC->GetHUD()))
	{
		// call the show result screen
		LavaHUD->ShowResultScreen(ResultWidgetClass, DeathMessage);
	}
	GetWorldTimerManager().ClearTimer(LevelTimer); // stop timer
	IsGameOver = true;
}

void ALavaGameMode::SetLavaSpeed(float Speed)
{
	Lava->SetLavaSpeed(Speed);
}
