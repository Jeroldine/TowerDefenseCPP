// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "TDPlayer.h"

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
	
	ATDPlayer* player = Cast<ATDPlayer>(UGameplayStatics::GetActorOfClass(this, ATDPlayer::StaticClass()));
	if (player)
	{
		// Bind the OnTowerBuilt event to the OnTowerBuiltHandler function
		player->OnCheckForValidPath.AddDynamic(this, &AGridManager::OnCheckForValidPathHandler);
	}
}

float AGridManager::TaxiCabHeuristic()
{
	return 0.0f;
}

float AGridManager::DamageHeuristic()
{
	return 0.0f;
}

float AGridManager::ChebyshevHeuristic()
{
	return 0.0f;
}

void AGridManager::UpdatePlacementMap(FIntPoint pos, int targetType, bool adding)
{
	switch (targetType)
	{
	case -1:
		undergroundTowerPlacementMap.Add(pos, adding ? 1 : 0);
		break;

	case 0:
		groundTowerPlacementMap.Add(pos, adding ? 1 : 0);
		break;

	case 1:
		aerialTowerPlacementMap.Add(pos, adding ? 1 : 0);
		break;

	default:
		break;
	}
}

void AGridManager::UpdateDamageMap(FIntPoint pos, int targetType, int range, float power, bool adding)
{
	switch (targetType)
	{
	case -1:
		UpdateDamageOnTiles(pos, range, power, adding ? 1 : -1, undergroundDamageMap);
		break;

	case 0:
		UpdateDamageOnTiles(pos, range, power, adding ? 1 : -1, groundDamageMap);
		break;

	case 1:
		UpdateDamageOnTiles(pos, range, power, adding ? 1 : -1, aerialDamageMap);
		break;

	default:
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Update Damage Map target type not valid"));
		break;
	}
}

void AGridManager::UpdateDamageOnTiles(FIntPoint center, int range, float power, float scale, TMap<FIntPoint, float>& dmgMap)
{
	int centerX = center.X;
	int centerY = center.Y;
	
	//dmgMap.Add(center, 1000.0f);
	dmgMap[center] += scale * 1000.0f;
	FIntPoint newPos = center;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Power: " + FString::FromInt(power)));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Range: " + FString::FromInt(range)));

	for (int i = 0; i < range; i++)
	{
		for (int j = 0; j < range-i; j++)
		{
			// if there is a valid tile when doing upper right quadrant
			if (centerX + j + 1 < actualGridRows && centerY + i < actualGridCols) 
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Valid upper right quadrant tile"));
				newPos.X = centerX + j + 1;
				newPos.Y = centerY + i;
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("newPos.X: " + FString::FromInt(newPos.X)));
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("newPos.Y: " + FString::FromInt(newPos.Y)));
				dmgMap[newPos] += scale * power;
			}
			// if there is a valid tile when doing lower right quadrant
			if (centerX - i + 1 > 0 && centerY + j + 1 < actualGridCols)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Valid lower right quadrant tile"));
				newPos.X = centerX - i;
				newPos.Y = centerY + j + 1;
				dmgMap[newPos] += scale * power;
			}
			// if there is a valid tile when doing lower left quadrant
			if (centerX - j > 0 && centerY - i + 1 > 0)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Valid lower left quadrant tile"));
				newPos.X = centerX - j - 1;
				newPos.Y = centerY - i;
				dmgMap[newPos] += scale * power;
			}
			// if there is a valid tile when doing upper left quadrant
			if (centerX + i < actualGridRows && centerY - j > 0)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Valid upper left quadrant tile"));
				newPos.X = centerX + i;
				newPos.Y = centerY - j - 1;
				dmgMap[newPos] += scale * power;
			}
		}
	}
}

void AGridManager::OnCheckForValidPathHandler(FIntPoint pos, TSet<int> targetTypes)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("OnTileHoveredStart Event heard in GridManager."));

	for (const int& element : targetTypes)
	{
	}
}

bool AGridManager::CheckForWayOut(FIntPoint pos, int targetType)
{
	
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

			groundTowerPlacementMap.Add(tile->GetGridPos(), 0);
			undergroundTowerPlacementMap.Add(tile->GetGridPos(), 0);
			aerialTowerPlacementMap.Add(tile->GetGridPos(), 0);

			groundDamageMap.Add(tile->GetGridPos(), 0.0f);
			undergroundDamageMap.Add(tile->GetGridPos(), 0.0f);
			aerialDamageMap.Add(tile->GetGridPos(), 0.0f);
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

ATile* AGridManager::GetTileAtPos(FIntPoint pos)
{
	return *mapOfTiles.Find(pos);
}

TMap<FIntPoint, int> AGridManager::GetPlacementMap(int type)
{
	switch (type)
	{
	case -1:
		return undergroundTowerPlacementMap;
	case 0:
		return groundTowerPlacementMap;
	case 1:
		return aerialTowerPlacementMap;
	default:
		return groundTowerPlacementMap;
	}
}

void AGridManager::UpdatePlacementAndDamageMaps(FIntPoint towerPos, TSet<int> towerTargets, int towerRange, float towerPower, bool addingTower)
{
	for (const int& targetType : towerTargets)
	{
		UpdatePlacementMap(towerPos, targetType, addingTower);
		UpdateDamageMap(towerPos, targetType, towerRange, towerPower, addingTower);
	}
}

TArray<FVector> AGridManager::FindPath(FIntPoint start, FIntPoint goal, UClass* enemyType)
{
	return TArray<FVector>();
}

TArray<FVector> AGridManager::RecoverPath()
{
	return TArray<FVector>();
}

TArray<float> AGridManager::GetDamageSpread()
{
	return TArray<float>();
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
