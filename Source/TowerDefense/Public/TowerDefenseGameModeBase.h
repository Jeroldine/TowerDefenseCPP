// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridManager.h"
#include "TowerDefenseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = GridManager)
	TSubclassOf<class AActor> GridManagerClass;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GridManager)
	int numGridRows = 7;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GridManager)
	int numGridCols = 15;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GridManager)
	float tileSize = 200.0f;

	// function that spawns the GridManager
	UFUNCTION()
	void SpawnGridManager(int rows, int cols, float sideLength);
};
