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

	// variables
	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int defaultGridRows = 8;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int defaultGridCols = 16;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	float defaulttileSize = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int minGridRows = 5;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int maxGridRows = 50;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int minGridCols = 3;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int maxGridCols = 100;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int minTileSize = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = Dimensions)
	int maxTileSize = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = Materials)
	UMaterial* tileMaterialMaster;

	UPROPERTY(VisibleAnywhere)
	TMap<FIntPoint, ATile*> mapOfTiles;

	UPROPERTY(VisibleAnywhere)
	FIntPoint startTilePos;

	UPROPERTY(VisibleAnywhere)
	FIntPoint goalTilePos;

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
	void ValidateDimensions();

	UFUNCTION()
	void SetStartGoal(FIntPoint start, FIntPoint goal);

	UFUNCTION()
	FIntPoint GetGoalTilePos();

	UFUNCTION()
	FIntPoint GetStartTilePos();
};
