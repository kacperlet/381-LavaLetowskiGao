// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultWidget.generated.h"

class UPoints;
class UButton;

/**
 * 
 */
UCLASS()
class LAVALETOWSKIGAO_API UResultWidget : public UUserWidget
{
	GENERATED_BODY()
	// connect to hud to get information:
	// the player loses when they run out of lives, or when the clock runs out, or when the lava rises above the roof hatch with the player still inside.
	
	// bind widget elements
	UPROPERTY(meta = (BindWidget))
	// displays the result -- Game Over if no lives/no time/lava too far
	// You Win if escape with 3 keys
	class UTextBlock* ResultText;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ResultButton;
	
protected:
	// UMG Construct Graph
	virtual void NativeConstruct() override;
	
public:	
	// the HUD
	TWeakObjectPtr<class ALavaHUD> OwningHUD;
	
	// pass in the HUD
	void InitializeResultScreen(class ALavaHUD* OwningHUD);
};
	