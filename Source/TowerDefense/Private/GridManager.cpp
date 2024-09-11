// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"

// Sets default values
AGridManager::AGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("GridManagerSceneComponent"));
	}
}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridManager::SpawnGrid(int nRows, int nCols, float sideLength)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Spawning Grid."));

	// uses default dimensions if bad data given
	ValidateDimensions(nRows, nCols, sideLength);

	for (int i = 0; i < actualGridRows; i++)
	{
		for (int j = 0; j < actualGridCols; j++)
		{
			ATile* tile = SpawnSingleTile(i, j, actualTileSize);
			if (tileMaterialMaster)
			{
				tile->SetMaterialInstance(tileMaterialMaster); // tile creates its own material instance
			}
			mapOfTiles.Add(tile->GetGridPos(), tile);
		}
	}
}

ATile* AGridManager::SpawnSingleTile(int row, int col, float targetSideLength)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		float xLocation = row * targetSideLength;
		float yLocation = col * targetSideLength;
		FVector location = FVector(xLocation, yLocation, 0.0);

		ATile* tile = World->SpawnActor<ATile>(tileClass, location, FRotator(0, 0, 0), SpawnParams);

		if (tile)
		{
			tile->Initialize(row, col, targetSideLength);
			tile->SetNeighbors(actualGridRows, actualGridCols);
			return tile;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No TileClass set in Blueprint."));
		}
	}
	return nullptr;
}

void AGridManager::ValidateDimensions(int rows, int cols, float size)
{
	actualGridRows = (rows < minGridRows || rows > maxGridRows) ? defaultGridRows : rows;
	actualGridCols = (cols < minGridCols || cols > maxGridCols) ? defaultGridCols : cols;
	actualTileSize = (size < minTileSize || size > maxTileSize) ? defaultTileSize : size;
}

void AGridManager::SetStartGoal(FIntPoint start, FIntPoint goal)
{
	// validate start tile
	if (start.X >= 0 && start.X < actualGridRows && start.Y == actualGridCols - 1)
		startTilePos = start;
	else
	{
		startTilePos.X = (actualGridRows / 2) - (actualGridRows / 4);
		startTilePos.Y = actualGridCols - 1;
	}

	// validate goal tile
	if (goal.X >= 0 && goal.X < actualGridRows && goal.Y == 0)
		goalTilePos = goal;
	else
	{
		goalTilePos.X = int(actualGridRows / 2) + int(actualGridRows / 4);
		goalTilePos.Y = 0;
	}	

	// set tiles as cannot build
	(*mapOfTiles.Find(startTilePos))->SetCanBuildOn(false);
	(*mapOfTiles.Find(goalTilePos))->SetCanBuildOn(false);
}

void AGridManager::SetFortressPos(FVector pos)
{
	fortressPos = pos;
}

FIntPoint AGridManager::GetGoalTilePos()
{
	return goalTilePos;
}

FIntPoint AGridManager::GetStartTilePos()
{
	return startTilePos;
}

void AGridManager::StartGamePlay()
{
}

void AGridManager::ResetActor()
{
	// reset each tile
	TArray<FIntPoint> keyArray;
	mapOfTiles.GenerateKeyArray(keyArray);
	for (FIntPoint key : keyArray)
		(*mapOfTiles.Find(key))->ResetActor();

	// set start and goal tiles as cannot build again
	(*mapOfTiles.Find(startTilePos))->SetCanBuildOn(false);
	(*mapOfTiles.Find(goalTilePos))->SetCanBuildOn(false);

	// reset data: placement maps
	for (TPair<FIntPoint, int>& Pair : groundTowerPlacementMap)
		Pair.Value = 0;

	for (TPair<FIntPoint, int>& Pair : undergroundTowerPlacementMap)
		Pair.Value = 0;

	for (TPair<FIntPoint, int>& Pair : aerialTowerPlacementMap)
		Pair.Value = 0;

	// reset data: damage maps
	for (TPair<FIntPoint, float>& Pair : groundDamageMap)
		Pair.Value = 0.0f;

	for (TPair<FIntPoint, float>& Pair : undergroundDamageMap)
		Pair.Value = 0.0f;

	for (TPair<FIntPoint, float>& Pair : aerialDamageMap)
		Pair.Value = 0.0f;
}
