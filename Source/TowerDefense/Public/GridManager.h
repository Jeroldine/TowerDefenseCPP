// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "GridManager.generated.h"

UCLASS()
class TOWERDEFENSE_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///////////////
	// variables //
	///////////////
	
	// actual
	UPROPERTY(VisibleAnywhere, Category = Dimensions)
	int actualGridRows = 8;

	UPROPERTY(VisibleAnywhere, Category = Dimensions)
	int actualGridCols = 16;

	UPROPERTY(VisibleAnywhere, Category = Dimensions)
	float actualTileSize = 200.0f;
	
	// defaults
	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int defaultGridRows = 8;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int defaultGridCols = 16;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	float defaultTileSize = 200.0f;

	// min/max rows
	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int minGridRows = 5;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int maxGridRows = 50;

	//min/max cols
	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int minGridCols = 3;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int maxGridCols = 100;

	// min/max tileSize
	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int minTileSize = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int maxTileSize = 400.0f;

	// start and goal
	UPROPERTY(VisibleAnywhere)
	FIntPoint startTilePos;

	UPROPERTY(VisibleAnywhere)
	FIntPoint goalTilePos;

	UPROPERTY(VisibleAnywhere)
	FVector fortressPos;

	// master tile material 
	UPROPERTY(EditDefaultsOnly, Category = Materials)
	UMaterial* tileMaterialMaster;

	// data storage
	UPROPERTY(VisibleAnywhere)
	TMap<FIntPoint, ATile*> mapOfTiles;

	UPROPERTY(VisibleAnywhere)
	TMap<FIntPoint, int> groundTowerPlacementMap;

	UPROPERTY(VisibleAnywhere)
	TMap<FIntPoint, int> undergroundTowerPlacementMap;

	UPROPERTY(VisibleAnywhere)
	TMap<FIntPoint, int> aerialTowerPlacementMap;

	// direction weights
	UPROPERTY(VisibleAnywhere)
	TMap<FIntPoint, float> groundDamageMap;

	UPROPERTY(VisibleAnywhere)
	TMap<FIntPoint, float> undergroundDamageMap;

	UPROPERTY(VisibleAnywhere)
	TMap<FIntPoint, float> aerialDamageMap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnGrid(int nRows, int nCols, float sideLength);

	UFUNCTION()
	ATile* SpawnSingleTile(int row, int col, float targetSideLength);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> tileClass;

// functions
	UFUNCTION()
	void ValidateDimensions(int row, int cols, float size);

	UFUNCTION()
	void SetStartGoal(FIntPoint start, FIntPoint goal);

	UFUNCTION()
	void SetFortressPos(FVector pos);

	UFUNCTION()
	FIntPoint GetGoalTilePos();

	UFUNCTION()
	FIntPoint GetStartTilePos();

	UFUNCTION()
	ATile* GetTileAtPos(FIntPoint pos);

	UFUNCTION()
	TArray<float> GetDamageSpread();

	UFUNCTION()
	void StartGamePlay();

	UFUNCTION()
	void ResetActor();
};
