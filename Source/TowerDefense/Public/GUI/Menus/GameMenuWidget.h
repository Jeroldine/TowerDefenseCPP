// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Menus/BaseMenuWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GUI/Buttons/TextButtonWidget.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "TDPlayer.h"
#include "GameMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()

	void NativeConstruct() override;

protected:

	void InitScreen() override;

public:

	///////////////
	// Functions //
	///////////////
	UFUNCTION()
	void ShowSubMenu(TSubclassOf<UBaseMenuWidget> newSubMenu);

	UFUNCTION()
	void ClearSubMenu(ESlateVisibility buildBtnHL, ESlateVisibility destroyBtnHL);

	UFUNCTION()
	void OnBuildClick();

	UFUNCTION()
	void OnDestroyClick();

	UFUNCTION()
	void OnCancelClick();

	UFUNCTION()
	void OnPauseClick();

	UFUNCTION()
	void UpdateScoreText(int newScore);

	UFUNCTION()
	void UpdateWaveText(int newWave);

	UFUNCTION()
	void UpdateHealthBar(float normalizedHealth);

	UFUNCTION()
	void UpdateMaterialsText(TArray<int> materials);

	///////////////
	// Varaibles //
	///////////////

	// buttons
	UPROPERTY(meta = (BindWidget))
	UTextButtonWidget* pauseButton;

	UPROPERTY(meta = (BindWidget))
	UTextButtonWidget* buildModeButton;

	UPROPERTY(meta = (BindWidget))
	UTextButtonWidget* destroyModeButton;

	UPROPERTY(meta = (BindWidget))
	UImage* buildBtnBackImage;

	UPROPERTY(meta = (BindWidget))
	UImage* destroyBtnBackImage;

	UPROPERTY(meta = (BindWidget))
	UTextButtonWidget* cancelModeButton;

	// other UI elements
	UPROPERTY(meta = (BindWidget))
	UTextBlock* scoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* waveText;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* healthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* buildMatText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* upgradeMat1Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* upgradeMat2Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* upgradeMat3Text;
	
	// submenus
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseMenuWidget> towerSelectMenu;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseMenuWidget> pauseMenu;

	UBaseMenuWidget* currentSubMenu;
	
};
