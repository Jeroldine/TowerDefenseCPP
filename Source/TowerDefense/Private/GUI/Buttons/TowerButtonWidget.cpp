// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Buttons/TowerButtonWidget.h"

void UTowerButtonWidget::SetButtonImage(UTexture2D* icon)
{
	if (ButtonImage && icon)
	{
		ButtonImage->SetBrushFromTexture(icon);
	}
}

void UTowerButtonWidget::SetTowerType(TSubclassOf<ATowerBase> type)
{
	towerType = type;
}

void UTowerButtonWidget::SetText(FString value)
{
	if (!Button || !ButtonText) return;

	ButtonText->SetText(FText::FromString(value));
	Button->OnClicked.AddDynamic(this, &UTowerButtonWidget::OnClick);
}

void UTowerButtonWidget::OnClick()
{
	ATDPlayer* tdPlayer = Cast<ATDPlayer>(UGameplayStatics::GetActorOfClass(this, ATDPlayer::StaticClass()));

	if (tdPlayer && towerType)
	{
		tdPlayer->RetrieveTower(towerType);
	}
}
