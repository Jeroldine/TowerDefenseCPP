// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridManager.h"
#include "Managers/TowerManager.h"
#include "Managers/EnemyManager.h"
#include "Fortress.h"
#include "TDPlayer.h"
#include "Math/IntPoint.h"
#include "Kismet/GameplayStatics.h"
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

	UPROPERTY(VisibleAnywhere)
	ATDPlayer* playerRef;

	UPROPERTY(VisibleAnywhere)
	int gameScore = 0;

	// game flow
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void ResetGame();

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

	UPROPERTY(EditDefaultsOnly)
	TArray<int> startingMaterials = { 1000, 0, 0, 0 };

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
	void RestartGame();

	UFUNCTION()
	void EndGame();

	UFUNCTION()
	void UpdateGameScore(int amount);

	UFUNCTION()
	int GetGameScore();
};
