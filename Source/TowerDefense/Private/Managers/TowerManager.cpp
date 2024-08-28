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

	CreateObjectPoolComponents();
}

// Called when the game starts or when spawned
void ATowerManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATowerManager::CreateObjectPoolComponents()
{
	for (UClass* pooledObjClass : pooledObjClasses)
	{
		if (pooledObjClass)
		{
			UObjectPoolComponent* objPoolComp = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("OjectPool"));
			//objPoolComp->SetObjectClass(pooledObjClass);
			//objectPoolComponents.Add(pooledObjClass, objPoolComp);
		}
	}
}

// Called every frame
void ATowerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

