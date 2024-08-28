// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Menus/GameMenuWidget.h"

void UGameMenuWidget::NativeConstruct()
{
	InitScreen();
}

void UGameMenuWidget::InitScreen()
{
	scoreText->SetText(FText::FromString("0"));
	healthBar->SetPercent(1.0f);

	buildMatText->SetText(FText::FromString("x 0"));
	upgradeMat1Text->SetText(FText::FromString("x 0"));
	upgradeMat2Text->SetText(FText::FromString("x 0"));
	upgradeMat3Text->SetText(FText::FromString("x 0"));

	//waveText->SetText
}
