// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "TextButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTextButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	UFUNCTION()
	void SetText(FString value);

private:
	 FString buttonText = "N/A";
	
};
