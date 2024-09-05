// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/Menus/BaseMenuWidget.h"
#include "GUI/Buttons/TextButtonWidget.h"
#include "GUI/TowerDefenseHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameOverMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameOverMenuWidget : public UBaseMenuWidget
{
	GENERATED_BODY()

	void NativeConstruct() override;

protected:

	void InitScreen() override;
	
public:

	// buttons
	UPROPERTY(meta = (BindWidget))
	UTextButtonWidget* replayButton;

	UPROPERTY(meta = (BindWidget))
	UTextButtonWidget* mainMenuButton;
};
