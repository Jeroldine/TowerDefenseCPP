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
	ValidateDimensions();

	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			ATile* tile = SpawnSingleTile(i, j, sideLength);
			if (tileMaterialMaster)
			{
				tile->SetMaterialInstance(tileMaterialMaster);
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
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Single tile spawned."));
			//tile->SetGridPos(row, col);
			tile->Initialize(row, col, targetSideLength);
			return tile;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No TileClass set in Blueprint."));
		}
	}
	return nullptr;
}

void AGridManager::ValidateDimensions()
{

}

void AGridManager::SetStartGoal(FIntPoint start, FIntPoint goal)
{


	startTilePos = start;
	goalTilePos = goal;
}

FIntPoint AGridManager::GetGoalTilePos()
{
	return goalTilePos;
}

FIntPoint AGridManager::GetStartTilePos()
{
	return startTilePos;
}
