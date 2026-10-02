// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LavaHUDWidget.h"
#include "GameFramework/HUD.h"
#include "LavaHUD.generated.h"

class ULavaHUDWidget;

// add reference to result widget
class UResultWidget;

/**
 * 
 */
UCLASS()
class LAVALETOWSKIGAO_API ALavaHUD : public AHUD
{	
	GENERATED_BODY()
public:
	ALavaHUD();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ULavaHUDWidget> HUDWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UResultWidget> ResultWidgetClass;
	// show result when game over
	virtual void ShowResultScreen();

private:
	UPROPERTY() ULavaHUDWidget* HUDWidget;
};
