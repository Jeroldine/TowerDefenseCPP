// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAICharacter.h"
#include "Components/CapsuleComponent.h"
#include "Enemies/EnemyAIController.h"
#include "Managers/EnemyManager.h"
#include "Tile.h"

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!healthComponent)
	{
		healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	}

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAICharacter::BeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AEnemyAICharacter::EndOverlap);

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

void AEnemyAICharacter::SetGridPos(FIntPoint pos)
{
	gridPos = pos;
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

void AEnemyAICharacter::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATile* tile = Cast<ATile>(OtherActor);
	if (tile)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Begin overlap with tile"));
		tile->AddOccupant(this);
	}
}

void AEnemyAICharacter::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATile* tile = Cast<ATile>(OtherActor);
	if (tile)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("End overlap with tile"));
		tile->RemoveOccupant(this);
	}
}

int AEnemyAICharacter::GetCurrentTerrainType()
{
	return currentTerrain;
}

void AEnemyAICharacter::RequestNewPath()
{
	
}

void AEnemyAICharacter::TakeHit(float dmg)
{
	if (healthComponent->GetHealth() > 0)
	{
		healthComponent->DecreaseHealth(dmg);
		float hp = healthComponent->GetHealth();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(hp));
	}

	if (healthComponent->GetHealth() <= 0)
	{
		AEnemyManager* enemyManager = Cast<AEnemyManager>(UGameplayStatics::GetActorOfClass(this, AEnemyManager::StaticClass()));
		FString enemyName;
		this->GetName(enemyName);
		enemyManager->RemoveActiveEnemy(enemyName);
		IPoolableInterface::Execute_Disable(this);
	}
}

float AEnemyAICharacter::GetHealth()
{
	return healthComponent->GetHealth();
}

int AEnemyAICharacter::GetPointsValue()
{
	return pointsValue;
}

TArray<int> AEnemyAICharacter::GetDroppedResources()
{
	return droppedResources;
}

bool AEnemyAICharacter::Initialize_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//GetCapsuleComponent()->CollisionPre
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);

	return false;
}

bool AEnemyAICharacter::Disable_Implementation()
{
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