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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnGrid(int nRows, int nCols, float sideLength);

	UFUNCTION()
	ATile* SpawnSingleTile(int row, int col, float targetSideLength);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> tileClass;
};
