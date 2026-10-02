// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LavaHUDWidget.h"
#include "GameFramework/HUD.h"
#include "LavaHUD.generated.h"

class ULavaHUDWidget;
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

private:
	UPROPERTY() ULavaHUDWidget* HUDWidget;
};
