// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaHUD.h"
#include "LavaHUDWidget.h"
#include "LavaGameMode.h"
#include "ResultWidget.h"

ALavaHUD::ALavaHUD()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// adds widget blueprint to HUD class
	static ConstructorHelpers::FClassFinder<ULavaHUDWidget> WidgetBPClass(
		TEXT("/Game/User_Interface/BP_LavaWidget"));
	if (WidgetBPClass.Succeeded())
	{
		HUDWidgetClass = WidgetBPClass.Class;
	}
}

void ALavaHUD::BeginPlay()
{
	Super::BeginPlay();

	// adds widget blueprint to HUD UI
	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<ULavaHUDWidget>(GetOwningPlayerController(), HUDWidgetClass);
		if (HUDWidget) HUDWidget->AddToViewport();
	}
}

void ALavaHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HUDWidget) return;
	if (const ALavaGameMode* Gm = GetWorld()->GetAuthGameMode<ALavaGameMode>())
	{
		HUDWidget->SetTimeRemaining(Gm->GetTimeRemaining());
		HUDWidget->SetKeys(Gm->GetKeysCollected());
		HUDWidget->SetLivesRemaining(Gm->GetLivesLeft());
		HUDWidget->SetLavaHeight(Gm->GetRiseHeight());
		HUDWidget->SetScore(Gm->GetScore());
	}
}

void ALavaHUD::ShowResultScreen(TSubclassOf<UResultWidget> WidgetClassToSpawn, FText DeathMessage)
{
	// remove HUD widget from screen
	if (HUDWidget)
	{
		HUDWidget->RemoveFromParent();
	}
	// put Result widget
	if (UResultWidget* ResultWidget = CreateWidget<UResultWidget>(GetWorld(), WidgetClassToSpawn))
	{
		// pass the HUD instance to the widget so it can run if-statements
		ResultWidget->InitializeResultScreen(this, DeathMessage, false);
		ResultWidget->AddToViewport();
		
		// make sure player has control so they can click the button
		if (APlayerController* PlayerController = GetOwningPlayerController())
		{
			PlayerController->SetShowMouseCursor(true);
			
			// ensure player can only click on the widget UI
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(ResultWidget->TakeWidget());
			PlayerController->SetInputMode(InputMode);
		}
	}
}