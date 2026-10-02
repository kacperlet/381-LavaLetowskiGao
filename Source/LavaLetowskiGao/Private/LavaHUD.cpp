// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaHUD.h"
#include "LavaHUDWidget.h"
#include "LavaGameMode.h"

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
		HUDWidget->SetLavaHeight(0);
		HUDWidget->SetScore(Gm->GetScore());
	}
}