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

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* TimeText;
};
