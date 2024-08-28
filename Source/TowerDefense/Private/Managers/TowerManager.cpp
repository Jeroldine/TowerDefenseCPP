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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Storing Object Pools in TMap."));
	TArray<UObjectPoolComponent*> objPools;
	GetComponents<UObjectPoolComponent>(objPools);

	for (UObjectPoolComponent* pool : objPools)
	{
		if (pool->GetObjectClass())
		{
			objectPoolComponents.Add(pool->GetObjectClass(), pool);
			FString str = FString(pool->GetObjectClass()->GetName());
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, str);
		}
	}
}

// Called every frame
void ATowerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

