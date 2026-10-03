// Fill out your copyright notice in the Description page of Project Settings.

#include "ResultWidget.h"
#include "Components/TextBlock.h"
#include "LavaGameMode.h"

void UResultWidget::InitializeResultScreen(ALavaHUD* LavaHUD)
{
	// check that HUD and UI text element both exist
	if (!LavaHUD || !ResultText) return;
	
	// pull data from HUD -- score / win
	
	// const ALavaGameMode* Gm = GetWorld()->GetAuthGameMode<ALavaGameMode>();
	// int32 FinalScore = Gm->GetScore();
	// bool bPlayerWin = LavaHUD->GetPlayerWin();
	
	// if (bPlayerWin)
	// {
	// 	// Use FString for Dynamic Text (to include score)
	// 	FString WinMessage = FString::Printf(TEXT("YOU WIN!\nFinal Score: %d"), FinalScore);
	// 	ResultText->SetText(FText::FromString(WinMessage));
	// }
	// else
	// {
	// 	FText LoseMessage = FText::FromString(TEXT("GAME OVER\nTry Again!"));
	// 	ResultText->SetText(LoseMessage);
	// }
	
	FText TestingMessage = FText::FromString(TEXT("Testing Text Replacement\nNew Line"));
	ResultText->SetText(TestingMessage);
}

void UResultWidget::NativeConstruct()
{
	Super::NativeConstruct();
}