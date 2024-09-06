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

	//UFUNCTION()
	//void Spawn

	///////////////
	// Variables //
	///////////////



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//functions

	UFUNCTION()
	void StartGamePlay();

	UFUNCTION()
	void ResetActor();

};
