// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Towers/TowerBase.h"
#include "Kismet/GameplayStatics.h"
#include "TDPlayer.h"
#include "Engine/Texture2D.h"
#include "TowerButtonWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API UTowerButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	UPROPERTY(meta = (BindWidget))
	UImage* ButtonImage;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATowerBase> towerType;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* towerIcon;

	UFUNCTION()
	void SetButtonImage(UTexture2D* icon);

	UFUNCTION()
	void SetTowerType(TSubclassOf<ATowerBase> type);

	UFUNCTION()
	void SetText(FString value);

	UFUNCTION()
	void OnClick();

private:
	FString buttonText = "N/A";

	
};
