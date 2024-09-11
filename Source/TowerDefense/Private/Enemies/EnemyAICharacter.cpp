// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAICharacter.h"

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!healthComponent)
	{
		healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	}
}

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyAICharacter::GetDamageAmount()
{
	return dmgAmount;
}

FVector AEnemyAICharacter::GetNextPointOnPath()
{
	if (currentPathIndex > pathPoints.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("current Index klarger than number of points in path"));
		return FVector(0, 0, -999);
	}
	else if (currentPathIndex == pathPoints.Num())
		return pathPoints[pathPoints.Num() - 1];
	
	currentPathIndex += 1;
	return pathPoints[currentPathIndex];
}

void AEnemyAICharacter::RequestNewPath()
{
	
}

bool AEnemyAICharacter::Initialize_Implementation()
{
	return false;
}

bool AEnemyAICharacter::Disable_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("EnemyAICharacter Disable implementation"));

	// get mesh and disable collisions
	SetActorLocation(FVector(0, 0, -500), false, nullptr, ETeleportType::TeleportPhysics);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	return false;
}

bool AEnemyAICharacter::Activate_Implementation()
{
	return false;
}