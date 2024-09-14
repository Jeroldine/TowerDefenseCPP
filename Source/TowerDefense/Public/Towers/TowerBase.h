// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/IntPoint.h"
#include "Helpers/PoolableInterface.h"
#include "Helpers/InteractableInterface.h"
#include "TowerBase.generated.h"

USTRUCT(BlueprintType)
struct FLevelRequirements
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<int> arr;

	int operator[] (int i)
	{
		return arr[i];
	}
};

class AEnemyAICharacter;

//TArray<FEncapsule> MyArray;
UCLASS(Blueprintable)
class TOWERDEFENSE_API ATowerBase : public AActor, public IPoolableInterface, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///////////////
	// Variables //
	///////////////
	UPROPERTY(VisibleAnywhere)
	int currentLevel = 0;

	UPROPERTY(EditDefaultsOnly)
	TArray<FLevelRequirements> requiredResources;

	UPROPERTY(VisibleAnywhere)
	TArray<int> investedResources;

	UPROPERTY(EditDefaultsOnly)
	float resourceRecoveryExtent = 0.5f;

	UPROPERTY(VisibleAnywhere)
	bool isPlaced = false;

	UPROPERTY(EditDefaultsOnly)
	int attackRange = 1;

	UPROPERTY(EditDefaultsOnly)
	float attackPower = 20.0f;

	UPROPERTY()
	FIntPoint gridPos;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* towerMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TSet<int> targetableTypes;


	///////////////
	// Functions //
	///////////////
	UFUNCTION(BlueprintCallable)
	void ResetTower();

	UFUNCTION(BlueprintCallable)
	virtual void BuildTower();

	UFUNCTION(BlueprintCallable)
	virtual void UpgradeTower();

	UFUNCTION(BlueprintCallable)
	virtual void DestroyTower();

	UFUNCTION(BlueprintCallable)
	void AddToInvestedResources();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///////////////
	// Functions //
	///////////////

	UFUNCTION()
	FIntPoint GetGridPos();

	UFUNCTION()
	void SetGridPos(FIntPoint pos);

	UFUNCTION()
	FLevelRequirements GetMaterialReqs();

	UFUNCTION()
	TArray<int> RecoverMaterials();

	UFUNCTION()
	bool GetIsPlaced();

	UFUNCTION()
	int GetAttackRange();

	UFUNCTION()
	float GetAttackPower();

	UFUNCTION()
	TSet<int> GetTargetableTypes();

	// Poolable Interface Implementations
	bool Initialize_Implementation() override;

	bool Disable_Implementation() override;

	bool Activate_Implementation() override;

	//Interactable Interface functions
	void OnClick_Implementation() override;

	void OnHoverStart_Implementation() override;

	void OnHoverStop_Implementation() override;
};
