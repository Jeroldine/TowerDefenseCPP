// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Helpers/HealthComponent.h"
#include "Helpers/PoolableInterface.h"
#include "EnemyAICharacter.generated.h"

UCLASS(Blueprintable)
class TOWERDEFENSE_API AEnemyAICharacter : public ACharacter, public IPoolableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	///////////////
	// Variables //
	///////////////
	UPROPERTY(EditDefaultsOnly)
	UHealthComponent* healthComponent;

	UPROPERTY(EditDefaultsOnly)
	float dmgAmount = 10.0f;

	UPROPERTY(EditAnywhere)
	TArray<FVector> pathPoints;

	UPROPERTY(EditDefaultsOnly)
	int currentPathIndex = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	///////////////
	// Variables //
	///////////////



	///////////////
	// Functions //
	///////////////

	UFUNCTION()
	float GetDamageAmount();

	UFUNCTION()
	FVector GetNextPointOnPath();

	UFUNCTION()
	void RequestNewPath();

	// IPoolableInterface functions
	bool Initialize_Implementation() override;

	bool Disable_Implementation() override;

	bool Activate_Implementation() override;
};
