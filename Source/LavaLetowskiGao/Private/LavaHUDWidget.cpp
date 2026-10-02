// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaHUDWidget.h"

void ULavaHUDWidget::SetTimeRemaining(int32 Seconds) const
{
	int32 const MinutesLeft = static_cast<int32>(Seconds / 60.0);
	int32 const SecondsLeft = static_cast<int32>(Seconds % 60);
	TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), MinutesLeft, SecondsLeft)));
}