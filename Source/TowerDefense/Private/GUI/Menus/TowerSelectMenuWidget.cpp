// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Menus/TowerSelectMenuWidget.h"

void UTowerSelectMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitScreen();
}

void UTowerSelectMenuWidget::InitScreen()
{
	TArray<TSubclassOf<ATowerBase>> keyArray;
	towerIconsMap.GenerateKeyArray(keyArray);

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			if (i * numRows + j >= keyArray.Num()) break;

			UUserWidget* widget = CreateWidget(this, towerButtonWidgetPrefab);
			buttonContainer->AddChildToGrid(widget, i, j);

			UTowerButtonWidget* button = Cast<UTowerButtonWidget>(widget); // Get Component in Unity
			TSubclassOf<ATowerBase> type = keyArray[i * numRows + j];
			button->SetButtonImage(*towerIconsMap.Find(type));
			button->SetTowerType(type);
			button->SetText((type->GetName()).Mid(3, (type->GetName()).Len() - 5));
		}
	}
}
