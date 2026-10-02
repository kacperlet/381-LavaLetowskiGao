// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameOverWidget.h"
#include "SlateOptMacros.h"


// we will not be using it for this game, but
// LOCTEXT is used for localization (when a game gets translated for example)
#define LOCTEXT_NAMESPACE "GameOverWidget"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SGameOverWidget::Construct(const FArguments& InArgs)
{
	// avoid annoying error message
	bCanSupportFocus = true;	
	
	// allows us to cache references to the hud
	OwningHUD = InArgs._OwningHUD;
	
	// button padding/margins
	const FMargin ContentPadding = FMargin(500.f, 300.f);
	const FMargin ButtonPadding = FMargin(10.f, 10.f);
	
	// LOCTEXT here uses "GameTitle" as a key for when/if the game gets localized
	const FText TitleText = LOCTEXT("GameTitle", "The Met Quest");
	const FText PlayText = LOCTEXT("PlayText", "Play");
	const FText GameOverText = LOCTEXT("GameOverText", "Game Over");
	
	// contains the content of the widget	
	ChildSlot
		[
			// using overlay, we can allow widgets to sit atop one another (stacked on the 'z-axis')
			SNew(SOverlay)

			// first slot -- represents the background layer
			// all subsequent slot sits on top of the previous (hence layers)
			+ SOverlay::Slot()

			// set horizontal and vertical alignment of the widget
			// "Fill" means that the widget fills the whole length
			// both H and V fill means that the widget takes the whole screen
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			
			// create a background (no image loaded, so the background is just our color (black)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]

			// new layer / slot -- on this layer we will put a text block
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			// set padding to our pre-defined padding size
			.Padding(ContentPadding)
			[
				// create a horizontal box
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					// our text
					SNew(STextBlock)
					.Text(TitleText)
					
				]

				+ SHorizontalBox::Slot()
				[
					// our text
					SNew(STextBlock)
					.Text(GameOverText)
				]

				// play button
				+ SHorizontalBox::Slot()
				.Padding(ButtonPadding)
				[
					SNew(SButton)
					[
						// putting text inside the button
						SNew(STextBlock)
						.Text(PlayText)
					]
				]
			]
		];
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
