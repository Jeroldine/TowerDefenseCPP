// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Menus/StartMenuWidget.h"

void UStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitScreen();
}


void UStartMenuWidget::InitScreen()
{
	startButton->SetText(FString("START"));
	quitButton->SetText(FString("QUIT"));

	ATowerDefenseHUD* towerDefHUD = GetTowerDefenseHUD();

	if (towerDefHUD)
	{
		startButton->Button->OnClicked.AddDynamic(towerDefHUD, &ATowerDefenseHUD::ShowGameMenu);
		quitButton->Button->OnClicked.AddDynamic(towerDefHUD, &ATowerDefenseHUD::QuitGame);
	}
	
}

void UStartMenuWidget::DeconfigScreen()
{
}

ATowerDefenseHUD* UStartMenuWidget::GetTowerDefenseHUD()
{
	return Super::GetTowerDefenseHUD();
}

AEnemyManager* UStartMenuWidget::GetEnemyManager()
{
	return nullptr;
}




