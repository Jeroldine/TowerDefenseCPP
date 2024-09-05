// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Menus/GameOverMenuWidget.h"

void UGameOverMenuWidget::NativeConstruct()
{
	InitScreen();
}

void UGameOverMenuWidget::InitScreen()
{
	replayButton->SetText(FString("REPLAY"));
	mainMenuButton->SetText(FString("MAIN MENU"));

	ATowerDefenseHUD* TDHUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<ATowerDefenseHUD>();
	if (TDHUD)
	{
		replayButton->Button->OnClicked.AddDynamic(TDHUD, &ATowerDefenseHUD::ShowGameMenu);
		mainMenuButton->Button->OnClicked.AddDynamic(TDHUD, &ATowerDefenseHUD::ShowStartMenu);
	}
}
