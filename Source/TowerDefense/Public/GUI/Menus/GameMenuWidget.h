// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Menus/BaseMenuWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GUI/Buttons/TextButtonWidget.h"
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


	///////////////
	// Varaibles //
	///////////////

	UPROPERTY(meta = (BindWidget))
	UTextButtonWidget* pauseButton;

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
	
};
