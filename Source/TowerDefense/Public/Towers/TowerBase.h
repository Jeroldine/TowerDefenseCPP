// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	UPROPERTY(EditAnywhere)
	int currentLevel = 0;

	UPROPERTY(EditAnywhere)
	TArray<FLevelRequirements> requiredResources;

	UPROPERTY(EditAnywhere)
	TArray<int> investedResources;

	UPROPERTY(EditAnywhere)
	float resourceRecoveryExtent = 0.5f;

	UPROPERTY(EditAnywhere)
	bool isPlaced = false;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* towerMeshComponent;

	///////////////
	// Functions //
	///////////////
	UFUNCTION()
	void ResetTower();

	UFUNCTION(BlueprintCallable)
	virtual void BuildTower();

	UFUNCTION(BlueprintCallable)
	virtual void UpgradeTower();

	UFUNCTION(BlueprintCallable)
	virtual void DestroyTower();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	///////////////
	// Functions //
	///////////////
	bool Initialize_Implementation() override;

	bool Disable_Implementation() override;

	bool Activate_Implementation() override;

	//Interactable Interface functions
	void OnClick_Implementation() override;

	void OnHoverStart_Implementation() override;

	void OnHoverStop_Implementation() override;
};
