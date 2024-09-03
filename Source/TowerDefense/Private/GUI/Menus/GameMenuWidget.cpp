// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Menus/GameMenuWidget.h"

void UGameMenuWidget::NativeConstruct()
{
	InitScreen();
}

void UGameMenuWidget::InitScreen()
{
	scoreText->SetText(FText::FromString("0"));
	healthBar->SetPercent(1.0f);

	buildMatText->SetText(FText::FromString("x 0"));
	upgradeMat1Text->SetText(FText::FromString("x 0"));
	upgradeMat2Text->SetText(FText::FromString("x 0"));
	upgradeMat3Text->SetText(FText::FromString("x 0"));

	pauseButton->SetText(FString("| |"));
	buildModeButton->SetText(FString("BUILD"));
	destroyModeButton->SetText(FString("DESTROY"));
	cancelModeButton->SetText(FString("X"));

	//waveText->SetText

	if (towerSelectMenu)
	{
		buildModeButton->Button->OnClicked.AddDynamic(this, &UGameMenuWidget::OnBuildClick);
		destroyModeButton->Button->OnClicked.AddDynamic(this, &UGameMenuWidget::OnDestroyClick);
		cancelModeButton->Button->OnClicked.AddDynamic(this, &UGameMenuWidget::OnCancelClick);
	}
}

void UGameMenuWidget::ShowSubMenu(TSubclassOf<UBaseMenuWidget> newGameMenu)
{
	if (currentSubMenu) {
		currentSubMenu->RemoveFromParent();
		currentSubMenu = nullptr;
	}

	if (newGameMenu) {
		currentSubMenu = CreateWidget<UBaseMenuWidget>(GetWorld(), newGameMenu);
		currentSubMenu->AddToViewport();
	}
}

void UGameMenuWidget::ClearSubMenu(ESlateVisibility buildBtnHL, ESlateVisibility destroyBtnHL)
{
	if (currentSubMenu)
	{
		currentSubMenu->RemoveFromParent();
		currentSubMenu = nullptr;
	}
	buildBtnBackImage->SetVisibility(buildBtnHL);
	destroyBtnBackImage->SetVisibility(destroyBtnHL);
}

void UGameMenuWidget::OnBuildClick()
{
	if (ATDPlayer* tdPlayer = Cast<ATDPlayer>(UGameplayStatics::GetActorOfClass(this, ATDPlayer::StaticClass())))
		if (tdPlayer->GetInBuildMode()) return;
	
	ShowSubMenu(towerSelectMenu);
	buildBtnBackImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	destroyBtnBackImage->SetVisibility(ESlateVisibility::Hidden);

	ATDPlayer* tdPlayer = Cast<ATDPlayer>(UGameplayStatics::GetActorOfClass(this, ATDPlayer::StaticClass()));
	tdPlayer->EnterBuildMode();
}

void UGameMenuWidget::OnDestroyClick()
{
	if (ATDPlayer* tdPlayer = Cast<ATDPlayer>(UGameplayStatics::GetActorOfClass(this, ATDPlayer::StaticClass())))
		if (tdPlayer->GetInDestroyMode()) return;
	
	ClearSubMenu(ESlateVisibility::Hidden, ESlateVisibility::SelfHitTestInvisible);

	ATDPlayer* tdPlayer = Cast<ATDPlayer>(UGameplayStatics::GetActorOfClass(this, ATDPlayer::StaticClass()));
	tdPlayer->EnterDestroyMode();
}

void UGameMenuWidget::OnCancelClick()
{
	if (ATDPlayer* tdPlayer = Cast<ATDPlayer>(UGameplayStatics::GetActorOfClass(this, ATDPlayer::StaticClass())))
		if (tdPlayer->GetInBuildMode() || tdPlayer->GetInDestroyMode())
		{
			ClearSubMenu(ESlateVisibility::Hidden, ESlateVisibility::Hidden);
			tdPlayer->ExitAllModes();
		}
}

void UGameMenuWidget::OnPauseClick()
{
}

void UGameMenuWidget::UpdateScoreText(int newScore)
{
	if (!scoreText) return;
	scoreText->SetText(FText::FromString(FString::FromInt(newScore)));
}

void UGameMenuWidget::UpdateWaveText(int newWave)
{
	if (!waveText) return;
	waveText->SetText(FText::FromString(FString::FromInt(newWave)));
}

void UGameMenuWidget::UpdateHealthBar(float newHealthPercentage)
{
	if (!healthBar) return;
	healthBar->SetPercent(newHealthPercentage);
}

void UGameMenuWidget::UpdateMaterialsText(TArray<int> materials)
{
	if (!buildMatText) return;
	if (!upgradeMat1Text) return;
	if (!upgradeMat2Text) return;
	if (!upgradeMat3Text) return;

	buildMatText->SetText(FText::FromString("x " + FString::FromInt(materials[0])));
	upgradeMat1Text->SetText(FText::FromString("x " + FString::FromInt(materials[1])));
	upgradeMat2Text->SetText(FText::FromString("x " + FString::FromInt(materials[2])));
	upgradeMat3Text->SetText(FText::FromString("x " + FString::FromInt(materials[3])));
}


