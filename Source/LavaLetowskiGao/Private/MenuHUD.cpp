// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "MenuHUD.h"
// #include "SGameOverWidget.h"
// #include "Widgets/SWeakWidget.h"
//
// // used to get the global engine pointer to add stuff to screen
// #include "Engine/Engine.h"
//
// void AMenuHUD::BeginPlay()
// {
// 	Super::BeginPlay();
// 	if ( GEngine && GEngine->GameViewport)
// 	{
// 		// set the owning hud
// 		GameOverWidget = SNew(SGameOverWidget).OwningHUD(this);
// 		
// 		// SAssignNew creates AND assigns a widget to a variable pointer
// 		GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(gameOverContainer, SWeakWidget).PossiblyNullContent(GameOverWidget.ToSharedRef()));
// 	}
// 	
// }