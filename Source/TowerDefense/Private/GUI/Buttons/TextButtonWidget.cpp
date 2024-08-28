// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Buttons/TextButtonWidget.h"

void UTextButtonWidget::SetText(FString value)
{
	if (!Button || !ButtonText) return;

	ButtonText->SetText(FText::FromString(value));
	//Button->OnClicked.AddDynamic(this, &UTextButtonWidget::OnButtonClick);
}