// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "GameFramework/PlayerController.h"
#include "BaseMenuWidget.generated.h"

/**
 * 
 */
class ATowerDefenseHUD;

UCLASS()
class TOWERDEFENSE_API UBaseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	

protected:

	// functions
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void InitScreen();

	UFUNCTION()
	virtual void DeconfigScreen();

	virtual ATowerDefenseHUD* GetTowerDefenseHUD();

public:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* canvas;

	
		
};
