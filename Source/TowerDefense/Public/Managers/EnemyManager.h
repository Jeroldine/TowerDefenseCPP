// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemies/EnemyAICharacter.h"
#include "Helpers/ObjectPoolComponent.h"
#include "Helpers/PoolableInterface.h"
#include "EnemyManager.generated.h"

UCLASS()
class TOWERDEFENSE_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///////////////
	// Functions //
	///////////////

	UFUNCTION()
	void GatherObjectPools();

	UFUNCTION()
	void ConstructNewWave();

	UFUNCTION()
	void UpdateWave(int wave);

	UFUNCTION()
	void SendOutEnemy();

	UFUNCTION()
	UClass* ChooseEnemyToSpawn(TArray<float> towerDamageSpread);

	///////////////
	// Variables //
	///////////////

	UPROPERTY(VisibleAnywhere)
	TMap<UClass*, UObjectPoolComponent*> objectPoolComponents;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AEnemyAICharacter>> typeGEnemies;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AEnemyAICharacter>> typeUEnemies;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AEnemyAICharacter>> typeAEnemies;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AEnemyAICharacter>> typeGUAEnemy;

	UPROPERTY(VisibleAnywhere)
	TArray<UClass*> waveOrder = {};

	UPROPERTY(VisibleAnywhere)
	TMap<FString, AEnemyAICharacter*> activeEnemies = {};

	UPROPERTY(VisibleAnywhere, Category = EnemySpawning)
	int currentWave = 0;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	int numStartingEnemies = 5;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	int additionalEnemies = 2;

	UPROPERTY(VisibleAnywhere, Category = EnemySpawning)
	int numEnemiesToSpawn = -1;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	float startSpawnTime = 5;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	float additionalSpawnTime = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = EnemySpawning)
	float currentSpawnTime = -1.0f;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	int intervalToIncreaseEnemiesSpawned = 3;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	int intervalToIncreaseHybridSpawnChance = 5;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	int intervalToIncreaseGUASpawnChance = 10;

	UPROPERTY(VisibleAnywhere, Category = EnemySpawning)
	float spawnInterval = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = EnemySpawning)
	float timeBetweenWaves = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = EnemySpawning)
	float spawnChanceHybridEnemy = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = EnemySpawning)
	float spawnChanceEnemyGUA = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	float additionalSpawnChance = 0.02f;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	float maxSpawnChanceHybrid = 0.7f;

	UPROPERTY(EditDefaultsOnly, Category = EnemySpawning)
	float maxSpawnChanceGUA = 0.26f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//functions

	UFUNCTION()
	void RemoveActiveEnemy(FString leavingEnemy);

	UFUNCTION()
	void ClearAllTimers();

	UFUNCTION()
	void StartGamePlay();

	UFUNCTION()
	void ResetActor();

	// Timer stuff
	FTimerHandle newWaveTimerHandle;
	UFUNCTION()
	void NewWaveTimerComplete();

	FTimerHandle enemySpawnTimerHandle;
};
