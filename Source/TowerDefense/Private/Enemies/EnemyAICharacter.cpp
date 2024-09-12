// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAICharacter.h"
#include "Components/CapsuleComponent.h"
#include "Enemies/EnemyAIController.h"
#include "Managers/EnemyManager.h"

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!healthComponent)
	{
		healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	}

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;
}

void AEnemyAICharacter::ResetBehaviorTree()
{
	AEnemyAIController* aiCtrl = Cast<AEnemyAIController>(GetController());
	if (aiCtrl)
	{
		// Restart the behavior tree
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Restarting behaviour tree"));
		aiCtrl->RunBehaviorTree(aiCtrl->startingBT);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No AIController?"));
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
	if (pathPoints.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No Path Points Given"));
		return GetActorLocation();
	}

	if (currentPathIndex > pathPoints.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("current Index larger than number of points in path"));
		return FVector(0, 0, 0);
	}
	else if (currentPathIndex == pathPoints.Num())
		return pathPoints[pathPoints.Num() - 1];
	
	return pathPoints[currentPathIndex++];
}

void AEnemyAICharacter::RequestNewPath()
{
	
}

bool AEnemyAICharacter::Initialize_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);

	return false;
}

bool AEnemyAICharacter::Disable_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("EnemyAICharacter Disable implementation"));

	// get mesh and disable collisions
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorLocation(FVector(0, 0, -500), false, nullptr, ETeleportType::TeleportPhysics);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	healthComponent->ResetHealth();

	//remove from active enemies map in enemy manager
	AEnemyManager* enemyManager = Cast<AEnemyManager>(UGameplayStatics::GetActorOfClass(this, AEnemyManager::StaticClass()));
	FString enemyName;
	this->GetName(enemyName);
	enemyManager->RemoveActiveEnemy(enemyName);

	return false;
}

bool AEnemyAICharacter::Activate_Implementation()
{
	return false;
}