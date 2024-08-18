// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/IntPoint.h"
#include "Helpers/InteractableInterface.h"
#include "Tile.generated.h"

UCLASS()
class TOWERDEFENSE_API ATile : public AActor, public IInteractableInterface
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

	UFUNCTION()
	void Initialize(int row, int col, float targetSideLength);

	void OnClick_Implementation() override;

	void OnHoverStart_Implementation() override;

	void OnHoverStop_Implementation() override;

	///////////////
	// variables //
	///////////////
	UPROPERTY(VisibleAnywhere)
	FIntPoint gridPos;

	UPROPERTY(EditDefaultsOnly)
	float sideLength;

	UPROPERTY(EditDefaultsOnly)
	float shrinkFactor = 0.98f;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* tileMeshComponent;
};
