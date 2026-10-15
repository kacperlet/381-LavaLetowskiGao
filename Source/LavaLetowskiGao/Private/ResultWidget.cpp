// Fill out your copyright notice in the Description page of Project Settings.

#include "ResultWidget.h"

#include "LavaGameInstance.h"
#include "Components/TextBlock.h"
#include "LavaGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UResultWidget::InitializeResultScreen(ALavaHUD* LavaHUD, FText DeathMessage, bool bWin)
{
	// check that HUD and UI text element both exist
	if (!LavaHUD || !ResultText) return;
	
	// pull data from GameMode -- score / win
	const ALavaGameMode* Gm = GetWorld()->GetAuthGameMode<ALavaGameMode>();
	int32 FinalScore = Gm->GetScore();
	Won = bWin;
	
	// Transfer score to game instance
	if (ULavaGameInstance* GI = Cast<ULavaGameInstance>(GetGameInstance()))
	{
		GI->Score = FinalScore;
	}
	
	if (bWin)
	{
		// Use FString for Dynamic Text (to include score)
		FString WinMessage = FString::Printf(TEXT("YOU WIN! Please play again!\nFinal Score: %d"), FinalScore);
		ResultText->SetText(FText::FromString(WinMessage));
		DeathMessageText->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		FString LoseMessage = FString::Printf(TEXT("Game Over! Try again!\nFinal Score: %d"), FinalScore);
		ResultText->SetText(FText::FromString(LoseMessage));
		DeathMessageText->SetText(DeathMessage);
	}
}

void UResultWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ResultButton)
	{
		ResultButton->OnClicked.AddDynamic(this, &UResultWidget::OnButtonClicked);
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Widget Constructed"));
	}
}

void UResultWidget::OnButtonClicked()
{
	FName LevelName;
	if (Won)
	{
		LevelName = TEXT("/Game/Levels/Lvl_GrandCentral");
	}
	else
	{
		LevelName = FName(UGameplayStatics::GetCurrentLevelName(GetWorld()));
	}
	
	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}
