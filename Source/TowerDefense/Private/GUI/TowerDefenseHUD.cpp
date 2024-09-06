// Fill out your copyright notice in the Description page of Project Settings.

#include "GUI/TowerDefenseHUD.h"
#include "TowerDefenseGameModeBase.h"

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
	ATowerDefenseGameModeBase* TDGameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (TDGameMode)
		TDGameMode->ResetGame();
}

void ATowerDefenseHUD::ShowGameMenu()
{
	ShowMenu(gameHUD);

	// start start everything get gamemode
	ATowerDefenseGameModeBase* TDGameMode= Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (TDGameMode)
		TDGameMode->RestartGame();
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

