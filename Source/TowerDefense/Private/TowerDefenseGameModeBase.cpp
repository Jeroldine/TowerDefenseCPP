// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefenseGameModeBase.h"

void ATowerDefenseGameModeBase::StartPlay()
{
    Super::StartPlay();

    check(GEngine != nullptr);

    // Display a debug message for five seconds. 
    // The -1 "Key" value argument prevents the message from being updated or refreshed.
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is TowerDefenseGameMode!"));

    /*int test = 10;
    bool boolTest = true;
    UE_LOG(LogTemp, Warning, TEXT("Test: %i, TestBool: %d, StringText: %s"), test, boolTest, TEXT("Test"));*/

    // Spawn things into the world
    SpawnGridManager(numGridRows, numGridCols, tileSize);
    SpawnTowerManager();
    SpawnEnemyManager();
    SpawnFortress();
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

            gridManagerRef = World->SpawnActor<AGridManager>(GridManagerClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);

            if (gridManagerRef)
            {
                // Successfully spawned the GridManager
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("GridManager spawned successfully."));
                // set starting and goal tiles


                //spawn grid
                gridManagerRef->SpawnGrid(rows, cols, sideLength);
                gridManagerRef->SetStartGoal(startTile, goalTile);
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

void ATowerDefenseGameModeBase::SpawnTowerManager()
{
    if (TowerManagerClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            towerManagerRef = World->SpawnActor<ATowerManager>(TowerManagerClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);

            if (towerManagerRef)
            {
                // Successfully spawned the GridManager
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("TowerManager spawned successfully."));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to spawn TowerManager."));
            }
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TowerManagerClass not set in TDGameMode Blueprint."));
    }
}

void ATowerDefenseGameModeBase::SpawnEnemyManager()
{
    if (EnemyManagerClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            enemyManagerRef = World->SpawnActor<AEnemyManager>(EnemyManagerClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);

            if (enemyManagerRef)
            {
                // Successfully spawned the GridManager
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("EnemyManager spawned successfully."));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to spawn EnemyManager."));
            }
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("EnemyManager not set in TDGameMode Blueprint."));
    }
}

void ATowerDefenseGameModeBase::SpawnFortress()
{
    if (FortressClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            // replace spawnposition
            float xLoc = (gridManagerRef->GetGoalTilePos()[0]) * tileSize;
            float yLoc = -(tileSize) * 1.2f;
            FVector spawnLoc = FVector(xLoc, yLoc, 0.0f);
            fortressRef = World->SpawnActor<AFortress>(FortressClass, spawnLoc, FRotator(0, 0, 0), SpawnParams);

            if (fortressRef)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Fortress spawned successfully."));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to spawn Fortress."));
            }
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Fortress not set in TDGameMode Blueprint."));
    }
}

void ATowerDefenseGameModeBase::StartGame()
{
    // trigger gameplay
}

void ATowerDefenseGameModeBase::ResetGame()
{
    // reset variables
}
