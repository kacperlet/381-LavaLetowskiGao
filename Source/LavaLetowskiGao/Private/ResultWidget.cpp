// Fill out your copyright notice in the Description page of Project Settings.

#include "ResultWidget.h"
#include "Components/TextBlock.h"
#include "LavaGameMode.h"

void UResultWidget::InitializeResultScreen(ALavaHUD* LavaHUD, FText DeathMessage, bool bWin)
{
	// check that HUD and UI text element both exist
	if (!LavaHUD || !ResultText) return;
	
	// pull data from HUD -- score / win
	
	// const ALavaGameMode* Gm = GetWorld()->GetAuthGameMode<ALavaGameMode>();
	// int32 FinalScore = Gm->GetScore();
	
	if (bWin)
	{
		// Use FString for Dynamic Text (to include score)
		// FString WinMessage = FString::Printf(TEXT("YOU WIN!\nFinal Score: %d"), FinalScore);
		// ResultText->SetText(FText::FromString(WinMessage));
		DeathMessageText->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		FText LoseMessage = FText::FromString(TEXT("GAME OVER, Try Again!"));
		ResultText->SetText(LoseMessage);
		DeathMessageText->SetText(DeathMessage);
	}
}

void UResultWidget::NativeConstruct()
{
	Super::NativeConstruct();
}