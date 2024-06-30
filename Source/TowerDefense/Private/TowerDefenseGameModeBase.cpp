// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenseGameModeBase.h"

void ATowerDefenseGameModeBase::StartPlay()
{
    Super::StartPlay();

    check(GEngine != nullptr);

    // Display a debug message for five seconds. 
    // The -1 "Key" value argument prevents the message from being updated or refreshed.
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is TowerDefenseGameMode!"));

    // Spawn things into the world
    SpawnGridManager(numGridRows, numGridCols, tileSize);
}

void ATowerDefenseGameModeBase::SpawnGridManager(int rows, int cols, float sideLength)
{
    if (GridManagerClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            AGridManager* GridManager = World->SpawnActor<AGridManager>(GridManagerClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);

            if (GridManager)
            {
                // Successfully spawned the GridManager
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("GridManager spawned successfully."));
                GridManager->SpawnGrid(rows, cols, sideLength);
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to spawn GridManager."));
            }
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("GridManagerClass not set in TDGameMode Blueprint."));
    }
    
}