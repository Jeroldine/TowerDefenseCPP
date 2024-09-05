// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	///////////////
	// Variables //
	///////////////
	UPROPERTY(EditAnywhere)
	float maxHealth = 100.0f;

	UPROPERTY(EditAnywhere)
	float health = 0.0f;

	UPROPERTY(EditAnywhere)
	float healthRegenRate = 1.0f;

	UPROPERTY(EditAnywhere)
	bool canRegen = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegenerateHealth(float deltaTime);

	void IncreaseHealth(float amount);

	void DecreaseHealth(float amonut);

	float GetHealth();

	float GetNormalizedHealth();

	void SetHealth(float amount);

	void ResetHealth();
		
};
