// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Towers/TowerBase.h"
#include "Helpers/ObjectPoolComponent.h"
#include "Helpers/PoolableInterface.h"
#include "TowerManager.generated.h"

UCLASS()
class TOWERDEFENSE_API ATowerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TMap<UClass*, UObjectPoolComponent*> objectPoolComponents;

	UFUNCTION()
	void GatherObjectPools();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	AActor* RequestTower(TSubclassOf<ATowerBase> towerType);

	UFUNCTION()
	void StartGamePlay();

	UFUNCTION()
	void ResetActor();

};
