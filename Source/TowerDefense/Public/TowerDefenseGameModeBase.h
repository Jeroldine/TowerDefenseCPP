// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridManager.h"
#include "Managers/TowerManager.h"
#include "Managers/EnemyManager.h"
#include "Fortress.h"
#include "Math/IntPoint.h"
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
	// classes to spawn
	UPROPERTY(EditDefaultsOnly, Category = GridManager)
	TSubclassOf<class AGridManager> GridManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = TowerManager)
	TSubclassOf<class ATowerManager> TowerManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = EnemyManager)
	TSubclassOf<class AEnemyManager> EnemyManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = Fortress)
	TSubclassOf<class AFortress> FortressClass;

	// ref to objects of above
	UPROPERTY(VisibleAnywhere)
	AGridManager* gridManagerRef;

	UPROPERTY(VisibleAnywhere)
	ATowerManager* towerManagerRef;

	UPROPERTY(VisibleAnywhere)
	AEnemyManager* enemyManagerRef;

	UPROPERTY(VisibleAnywhere)
	AFortress* fortressRef;

public:
	UPROPERTY(EditDefaultsOnly, Category = GridManager)
	int numGridRows = 7;

	UPROPERTY(EditDefaultsOnly, Category = GridManager)
	int numGridCols = 15;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GridManager)
	float tileSize = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = GridManager)
	FIntPoint startTile;

	UPROPERTY(EditDefaultsOnly, Category = GridManager)
	FIntPoint goalTile;

	// functions to spawn actors
	UFUNCTION()
	void SpawnGridManager(int rows, int cols, float sideLength);

	UFUNCTION()
	void SpawnTowerManager();

	UFUNCTION()
	void SpawnEnemyManager();

	UFUNCTION()
	void SpawnFortress();

	// game flow
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void ResetGame();
};
