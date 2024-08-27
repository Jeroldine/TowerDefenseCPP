// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/TowerDefenseHUD.h"

void ATowerDefenseHUD::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Tower Defense HUD")));

	ShowMenu(startMenu);
}

void ATowerDefenseHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ATowerDefenseHUD::ShowMenu(TSubclassOf<UBaseMenuWidget> newGameMenu)
{
	if (currentMenu) {
		currentMenu->RemoveFromParent();
		currentMenu = nullptr;
	}

	if (newGameMenu) {
		currentMenu = CreateWidget<UBaseMenuWidget>(GetWorld(), newGameMenu);
		currentMenu->AddToViewport();
	}
}

void ATowerDefenseHUD::ShowStartMenu()
{
	ShowMenu(startMenu);
}

void ATowerDefenseHUD::ShowGameMenu()
{
	ShowMenu(gameHUD);
}

void ATowerDefenseHUD::ShowGameOverMenu()
{
	ShowMenu(gameOverMenu);
}

void ATowerDefenseHUD::QuitGame()
{
	if (APlayerController* PC = this->PlayerOwner)
	{
		PC->ConsoleCommand("quit");
	}
}

