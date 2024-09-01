// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/Menus/BaseMenuWidget.h"
#include "GUI/TowerDefenseHUD.h"


void UBaseMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("base menu native construct")));
}

void UBaseMenuWidget::InitScreen()
{
}

void UBaseMenuWidget::DeconfigScreen()
{
}

ATowerDefenseHUD* UBaseMenuWidget::GetTowerDefenseHUD()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Getting TD HUD")));
    // Get the owning player controller
    APlayerController* OwningPlayer = GetOwningPlayer();

    if (OwningPlayer)
    {
        // Get the HUD and cast it to your custom HUD class
        return Cast<ATowerDefenseHUD>(OwningPlayer->GetHUD());
    }
    
    return nullptr;
}




