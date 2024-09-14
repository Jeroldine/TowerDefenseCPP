// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/EnemyManager.h"
#include "GridManager.h"
#include "GUI/TowerDefenseHUD.h"
#include "GUI/Menus/GameMenuWidget.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyManagerSceneComponent"));
	}
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
	GatherObjectPools();
}

void AEnemyManager::GatherObjectPools()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Storing Enemy Object Pools in TMap."));
	TArray<UObjectPoolComponent*> objPools;
	GetComponents<UObjectPoolComponent>(objPools);

	for (UObjectPoolComponent* pool : objPools)
	{
		if (pool->GetObjectClass())
		{
			objectPoolComponents.Add(pool->GetObjectClass(), pool);
		}
	}
}

void AEnemyManager::ConstructNewWave()
{
	currentWave += 1;
	UpdateWave(currentWave);

	if (currentWave % intervalToIncreaseEnemiesSpawned == 0) // increase number of enemies spawned
	{
		numEnemiesToSpawn += additionalEnemies;
		currentSpawnTime += additionalSpawnTime;
		spawnInterval = float(numEnemiesToSpawn) / currentSpawnTime;
		waveOrder.Reserve(numEnemiesToSpawn);
	}
	else if (currentWave % intervalToIncreaseHybridSpawnChance == 0)
	{
		if (spawnChanceHybridEnemy < maxSpawnChanceHybrid)
			spawnChanceHybridEnemy += additionalSpawnChance;
	}
	else if (currentWave % intervalToIncreaseGUASpawnChance == 0)
	{
		if (spawnChanceEnemyGUA < maxSpawnChanceGUA)
			spawnChanceEnemyGUA += additionalSpawnChance;
	}
		
	// loop numEnemiesToSpawn times to create a list of enemy classes to spawn
	// can use info from grid manager -> compare damage maps to determine which enemy to spawn
	AGridManager* gridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(this, AGridManager::StaticClass()));
	TArray<float> damageSpread = gridManager->GetDamageSpread();
	for (int i = 0; i < numEnemiesToSpawn; i++)
	{
		waveOrder.Add(ChooseEnemyToSpawn(damageSpread));
	}
}

void AEnemyManager::UpdateWave(int wave)
{
	ATowerDefenseHUD* TDHUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<ATowerDefenseHUD>();
	if (TDHUD)
	{
		UGameMenuWidget* gameMenu = Cast<UGameMenuWidget>(TDHUD->currentMenu);
		if (gameMenu)
			gameMenu->UpdateWaveText(wave);
	}
}

void AEnemyManager::SendOutEnemy()
{
	UClass* enemyType = waveOrder.Pop();
	UObjectPoolComponent* objPool = *objectPoolComponents.Find(enemyType);

	AEnemyAICharacter* enemy = Cast<AEnemyAICharacter>(objPool->SpawnObject()); //get object from pool
	FVector spawnLoc = FVector(GetActorLocation().X, GetActorLocation().Y, enemy->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());
	enemy->SetActorLocation(spawnLoc, false, nullptr, ETeleportType::TeleportPhysics); // set starting location
	
	FString actorName;
	enemy->GetName(actorName);

	activeEnemies.Add(actorName, enemy); // add it to list of active enemies

	if (waveOrder.Num() == 0)
		GetWorld()->GetTimerManager().ClearTimer(enemySpawnTimerHandle);
}

UClass* AEnemyManager::ChooseEnemyToSpawn(TArray<float> towerDamageSpread)
{
	return typeGEnemies[0];
}

void AEnemyManager::RemoveActiveEnemy(FString leavingEnemy)
{
	if (activeEnemies.Contains(leavingEnemy))
		activeEnemies.Remove(leavingEnemy);

	// check if no more enemies to spawn and no more active enemies
	if (waveOrder.Num() == 0 && activeEnemies.Num() == 0)
	{
		ConstructNewWave();
		StartGamePlay();
	}
}

void AEnemyManager::ClearAllTimers()
{
	GetWorld()->GetTimerManager().ClearTimer(newWaveTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(enemySpawnTimerHandle);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::NewWaveTimerComplete()
{
	GetWorldTimerManager().SetTimer(enemySpawnTimerHandle, this, &AEnemyManager::SendOutEnemy, spawnInterval, true);
}

void AEnemyManager::StartGamePlay()
{
	GetWorldTimerManager().SetTimer(newWaveTimerHandle, this, &AEnemyManager::NewWaveTimerComplete, timeBetweenWaves, false);
}

void AEnemyManager::ResetActor()
{
	currentWave = 0;
	waveOrder.Empty();
	numEnemiesToSpawn = numStartingEnemies;
	currentSpawnTime = startSpawnTime;
	activeEnemies.Empty(numEnemiesToSpawn);
	spawnInterval = startSpawnTime / float(numStartingEnemies);
	spawnChanceHybridEnemy = 0.0f;
	spawnChanceEnemyGUA = 0.0f;

	TArray<UClass*> keyArray;
	objectPoolComponents.GenerateKeyArray(keyArray);

	for (UClass* enemyType : keyArray)
	{
		UObjectPoolComponent* objPool = *objectPoolComponents.Find(enemyType);
		objPool->ReturnAllToPool();
	}

	ClearAllTimers();
	ConstructNewWave();
}



