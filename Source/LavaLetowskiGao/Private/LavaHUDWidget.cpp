// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaHUDWidget.h"

void ULavaHUDWidget::SetTimeRemaining(int32 Seconds) const
{
	int32 const MinutesLeft = static_cast<int32>(Seconds / 60.0);
	int32 const SecondsLeft = static_cast<int32>(Seconds % 60);
	TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), MinutesLeft, SecondsLeft)));
}

void ULavaHUDWidget::SetKeys(int32 Keys) const
{
	KeyText->SetText(FText::FromString(FString::Printf(TEXT("%d/3 Keys"), Keys)));
}

void ULavaHUDWidget::SetLivesRemaining(int32 Lives) const
{
	LivesText->SetText(FText::FromString(FString::Printf(TEXT("%d Lives"), Lives)));
}

void ULavaHUDWidget::SetLavaHeight(int32 LavaHeight) const
{
	LavaHeightText->SetText(FText::FromString(FString::Printf(TEXT("Lava %dcm"), LavaHeight)));
}

void ULavaHUDWidget::SetScore(int32 Score) const
{
	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d Points"), Score)));
}

void ULavaHUDWidget::SetHurtOverlayVisible(bool bVisible) const
{
	if (HurtOverlayImage)
	{
		HurtOverlayImage->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}
