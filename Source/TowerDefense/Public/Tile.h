// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/IntPoint.h"
#include "Helpers/InteractableInterface.h"
#include "Towers/TowerBase.h"
#include "Enemies/EnemyAICharacter.h"
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

	UPROPERTY(VisibleAnywhere)
	FIntPoint gridPos;

	UPROPERTY(EditDefaultsOnly)
	float sideLength;

	UPROPERTY(EditDefaultsOnly)
	float shrinkFactor = 0.98f;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* tileMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UMaterialInstanceDynamic* tileMaterialInstance;

	UPROPERTY(VisibleAnywhere)
	FLinearColor defaultColor;

	UPROPERTY(VisibleAnywhere)
	bool canBuildOn = true;

	UPROPERTY(VisibleAnywhere)
	TMap<FString, AActor*> occupantsMap;

	UPROPERTY(VisibleAnywhere)
	TArray<FIntPoint> neighborsArray;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///////////////
	// functions //
	///////////////
	UFUNCTION()
	FIntPoint GetGridPos();

	//Set up
	UFUNCTION()
	void SetGridPos(int row, int col);

	UFUNCTION()
	void Initialize(int row, int col, float targetSideLength);

	UFUNCTION()
	void SetMaterialInstance(UMaterial* masterMaterial);

	//Interface functions
	void OnClick_Implementation() override;

	void OnHoverStart_Implementation() override;

	void OnHoverStop_Implementation() override;

	// utilities
	UFUNCTION()
	void SetMaterialColor(FLinearColor newColor);

	UFUNCTION()
	int GetNumOccupants();

	UFUNCTION()
	void AddOccupant(AActor* newOccupant);

	UFUNCTION()
	void RemoveOccupant(AActor* leavingOccupantName);

	UFUNCTION()
	void SetCanBuildOn(bool canBuild);

	UFUNCTION()
	bool GetCanBuildOn();

	UFUNCTION()
	bool CheckForTowerOccupant();

	UFUNCTION()
	bool CheckForEnemyOccupant();
	
	UFUNCTION()
	void ResetActor();

	UFUNCTION()
	TArray<FIntPoint> GetNeighbors();

	UFUNCTION()
	void SetNeighbors(int maxRows, int maxCols);

};
