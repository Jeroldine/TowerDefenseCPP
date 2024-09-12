// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/TowerManager.h"

// Sets default values
ATowerManager::ATowerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TowerSceneComponent"));
	}
}

// Called when the game starts or when spawned
void ATowerManager::BeginPlay()
{
	Super::BeginPlay();
	
	GatherObjectPools();
}

void ATowerManager::GatherObjectPools()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Storing Tower Object Pools in TMap."));
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

// Called every frame
void ATowerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* ATowerManager::RequestTower(TSubclassOf<ATowerBase> towerType)
{
	UObjectPoolComponent* objPool = *objectPoolComponents.Find(towerType);

	return objPool->SpawnObject();
}

void ATowerManager::StartGamePlay()
{
}

void ATowerManager::ResetActor()
{
	TArray<UClass*> keyArray;
	objectPoolComponents.GenerateKeyArray(keyArray);

	for (UClass* towerType : keyArray)
	{
		UObjectPoolComponent* objPool = *objectPoolComponents.Find(towerType);
		objPool->ReturnAllToPool();
	}
}

