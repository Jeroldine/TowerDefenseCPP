// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Menus/BaseMenuWidget.h"
#include "GUI/TowerDefenseHUD.h"
#include "GUI/Buttons/TowerButtonWidget.h"
#include "Components/VerticalBox.h"
#include "Components/GridPanel.h"
#include "TowerSelectMenuWidget.generated.h"

/**
 * 
 */

//class ATowerG;
//class ATowerU;
//class ATowerA;
//class ATowerGU;
//class ATowerGA;
//class ATowerUA;
//class ATowerGUA;
class ATowerBase;

UCLASS()
class TOWERDEFENSE_API UTowerSelectMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

	void InitScreen() override;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* buttonContainer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UTowerButtonWidget> towerButtonWidgetPrefab;

	// gridSize
	UPROPERTY(EditDefaultsOnly)
	int numRows = 3;

	UPROPERTY(EditDefaultsOnly)
	int numCols = 3;
	
	// tower icons
	UPROPERTY(EditDefaultsOnly)
	TMap<TSubclassOf<ATowerBase>, UTexture2D*> towerIconsMap;

};
