// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBase.h"
#include "Enemies/EnemyAICharacter.h"
#include "Towers/Projectile.h"

// Sets default values
ATowerBase::ATowerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	investedResources.Init(0, 4);

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TowerSceneComponent"));
	}

	if (!detectionSphere)
	{
		detectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		detectionSphere->InitSphereRadius(250.0f);
		detectionSphere->SetupAttachment(RootComponent);

		detectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerBase::BeginOverlap);
		detectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerBase::EndOverlap);
	}

	if (!towerMeshComponent)
	{
		towerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
		towerMeshComponent->SetupAttachment(RootComponent);
	}

	if (!projectileSpawnPoint)
	{
		projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
		projectileSpawnPoint->SetupAttachment(RootComponent);
	}

}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATowerBase::ResetTower()
{
	currentLevel = 0;
	isPlaced = false;
	targetList.Empty();
	GetWorldTimerManager().ClearTimer(shootTimerHandle);
	
	for (int i = 0; i < investedResources.Num(); i++)
	{
		investedResources[i] = 0;
	}

}

void ATowerBase::BuildTower()
{
	isPlaced = true;

	for (int i = 0; i < investedResources.Num(); i++)
	{
		investedResources[i] = requiredResources[0][i];
	}

	currentLevel += 1;
}

void ATowerBase::UpgradeTower()
{
	if (currentLevel >= requiredResources.Num()) return;

	// apply upgrade
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TowerBase Upgrade Tower"));

	// record how many resources used to build and upgrade
	for (int i = 0; i < investedResources.Num(); i++)
		investedResources[i] += requiredResources[currentLevel][i];

	currentLevel += 1;
}

void ATowerBase::DestroyTower()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TowerBase Destroy Tower"));
}

void ATowerBase::AddToInvestedResources()
{
}

void ATowerBase::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyAICharacter* enemyAI = Cast<AEnemyAICharacter>(OtherActor);
	if (enemyAI)
	{
		FString actorName;
		enemyAI->GetName(actorName);
		/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, actorName);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("entered Range"));*/
		//add to target list
		AddEnemyToTargetList(enemyAI);
	}
}

void ATowerBase::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEnemyAICharacter* enemyAI = Cast<AEnemyAICharacter>(OtherActor);
	if (enemyAI)
	{
		FString actorName;
		enemyAI->GetName(actorName);
		/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, actorName);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("left Range"));*/
		//remove from target list
		RemoveEnemyFromTargetList(enemyAI);
	}
}

void ATowerBase::AddEnemyToTargetList(AEnemyAICharacter* enemy)
{
	FString actorName;
	enemy->GetName(actorName);
	targetList.Add(actorName, enemy);
	if (!GetWorldTimerManager().IsTimerActive(shootTimerHandle)) // condition is true if encountering enemy for first time
		Shoot();  
}

void ATowerBase::RemoveEnemyFromTargetList(AEnemyAICharacter* enemy)
{
	FString actorName;
	enemy->GetName(actorName);
	if (targetList.Contains(actorName))
		targetList.Remove(actorName);
}

void ATowerBase::Shoot()
{
	if (targetList.Num() != 0) // if there are targets
	{
		TArray<FString> keyArray;
		targetList.GenerateKeyArray(keyArray);
		for (FString key : keyArray) // check if any have a matching terrain type that can be targeted
		{
			AEnemyAICharacter* target = *targetList.Find(key);
			if (target && targetableTypes.Contains(target->GetCurrentTerrainType()))
			{
				UWorld* World = GetWorld();
				if (World && ProjectileClass)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = GetInstigator();
					AProjectile* projectile = World->SpawnActor<AProjectile>(ProjectileClass, projectileSpawnPoint->GetComponentLocation(),
						FRotator::ZeroRotator, SpawnParams);

					if (projectile)
					{
						FVector launchDirection = (target->GetActorLocation() - projectileSpawnPoint->GetComponentLocation()).GetSafeNormal();
						/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (target->GetActorLocation()).ToString());
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, (GetActorLocation()).ToString());*/
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, launchDirection.ToString());
						projectile->FireInDirection(launchDirection, attackPower);
						// set timer to shoot again
						GetWorldTimerManager().SetTimer(shootTimerHandle, this, &ATowerBase::Shoot, attackRate, false);
					}
					break;
				}
			}
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(shootTimerHandle);
	}
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FIntPoint ATowerBase::GetGridPos()
{
	return gridPos;
}

void ATowerBase::SetGridPos(FIntPoint pos)
{
	gridPos = pos;
}

FLevelRequirements ATowerBase::GetMaterialReqs()
{
	return requiredResources[currentLevel];
}

TArray<int> ATowerBase::RecoverMaterials()
{
	TArray<int> recoveredMatls = { 0, 0, 0, 0 };
	for (int i = 0; i < investedResources.Num(); i++)
		recoveredMatls[i] = investedResources[i] * resourceRecoveryExtent;

	return recoveredMatls;
}

bool ATowerBase::GetIsPlaced()
{
	return isPlaced;
}

int ATowerBase::GetAttackRange()
{
	return attackRange;
}

float ATowerBase::GetAttackPower()
{
	return attackPower;
}

TSet<int> ATowerBase::GetTargetableTypes()
{
	return targetableTypes;
}

bool ATowerBase::Initialize_Implementation()
{
	SetActorLocation(FVector(0, 0, 0), false, nullptr, ETeleportType::TeleportPhysics);
	SetActorHiddenInGame(false);

	return true;
}

bool ATowerBase::Disable_Implementation()
{
	detectionSphere->SetGenerateOverlapEvents(false);
	towerMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorLocation(FVector(0, 0, -500), false, nullptr, ETeleportType::TeleportPhysics);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	ResetTower();

	return true;
}

bool ATowerBase::Activate_Implementation()
{
	detectionSphere->SetGenerateOverlapEvents(true);
	towerMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	BuildTower();
	
	return true;
}

void ATowerBase::OnClick_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("TowerBase OnClick implementation"));
}

void ATowerBase::OnHoverStart_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("TowerBase OnHoverStart implementation"));
}

void ATowerBase::OnHoverStop_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("TowerBase OnHoverStop implementation"));
}
