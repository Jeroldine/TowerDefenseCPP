// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/IntPoint.h"
#include "Tile.generated.h"

UCLASS()
class TOWERDEFENSE_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///////////////
	// functions //
	///////////////
	UFUNCTION()
	FIntPoint GetGridPos();

	UFUNCTION()
	void SetGridPos(int row, int col);

	///////////////
	// variables //
	///////////////
	UPROPERTY(VisibleAnywhere)
	FIntPoint gridPos;


};
