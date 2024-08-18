// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::RegenerateHealth(float deltaTime)
{
	if (canRegen)
	{
		IncreaseHealth(deltaTime * healthRegenRate);
		canRegen = health < maxHealth;
	}
}

void UHealthComponent::IncreaseHealth(float amount)
{
	health = FMath::Clamp(health + amount, 0.0f, maxHealth);
}

void UHealthComponent::DecreaseHealth(float amount)
{
	health = FMath::Clamp(health - amount, 0.0f, maxHealth);
}

float UHealthComponent::GetHealth()
{
	return health;
}

float UHealthComponent::GetNormalizedHealth()
{
	return FMath::Clamp(health / maxHealth, 0.0f, 1.0f);
}

