// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Menus/BaseMenuWidget.h"
#include "GUI/Buttons/TextButtonWidget.h"
#include "GUI/TowerDefenseHUD.h"
#include "StartMenuWidget.generated.h"

/**
 * 
 */

class AEnemyManager;

UCLASS()
class TOWERDEFENSE_API UStartMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()	

protected:
	void NativeConstruct() override;

	void InitScreen() override;

	void DeconfigScreen() override;

	ATowerDefenseHUD* GetTowerDefenseHUD() override;
	AEnemyManager* GetEnemyManager();

public:
	///////////////
	// Functions //
	///////////////

	//void OnStartPressed();

	//void OnQuitPressed();

	///////////////
	// Varaibles //
	///////////////

	UPROPERTY(meta = (BindWidget))
	UTextButtonWidget* startButton;

	UPROPERTY(meta = (BindWidget))
	UTextButtonWidget* quitButton;
};
