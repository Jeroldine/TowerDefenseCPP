// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GUI/Menus/BaseMenuWidget.h"
#include "TowerDefenseHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	// UMG
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UBaseMenuWidget> startMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UBaseMenuWidget> gameHUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GUI")
	TSubclassOf<UBaseMenuWidget> gameOverMenu;

	UBaseMenuWidget* currentMenu;

	///////////////
	// FUNCTIONS //
	///////////////
	UFUNCTION(BlueprintCallable)
	void ShowMenu(TSubclassOf<UBaseMenuWidget> newGameMenu);

	UFUNCTION(BlueprintCallable)
	void ShowStartMenu();

	UFUNCTION(BlueprintCallable)
	void ShowGameMenu();

	UFUNCTION(BlueprintCallable)
	void ShowGameOverMenu();

	UFUNCTION(BlueprintCallable)
	void QuitGame();
};
