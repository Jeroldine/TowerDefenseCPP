// Fill out your copyright notice in the Description page of Project Settings.

#include "GUI/TowerDefenseHUD.h"
#include "TowerDefenseGameModeBase.h"
#include "GUI/Menus/GameMenuWidget.h"
#include "GUI/Menus/GameOverMenuWidget.h"

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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("TDHUD removing current menu")));
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
	/*if (TDGameMode)
		TDGameMode->ResetGame();*/
}

void ATowerDefenseHUD::ShowGameMenu()
{
	ShowMenu(gameHUD);

	// start start everything get gamemode
	ATowerDefenseGameModeBase* TDGameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (TDGameMode)
		TDGameMode->RestartGame();
}

void ATowerDefenseHUD::ShowGameOverMenu()
{
	ShowMenu(gameOverMenu);

	ATowerDefenseGameModeBase* TDGameMode = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (TDGameMode)
		TDGameMode->EndGame();
}

void ATowerDefenseHUD::QuitGame()
{
	if (APlayerController* PC = this->PlayerOwner)
	{
		PC->ConsoleCommand("quit");
	}
}

