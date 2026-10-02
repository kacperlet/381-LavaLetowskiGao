// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "LavaHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class LAVALETOWSKIGAO_API ULavaHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetTimeRemaining(int32 Seconds) const;
	void SetKeys(int32 Keys) const;
	void SetLivesRemaining(int32 Lives) const;
	void SetLavaHeight(int32 LavaHeight) const;
	void SetScore(int32 Score) const;

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* TimeText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* KeyText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* LivesText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* LavaHeightText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ScoreText;
};
