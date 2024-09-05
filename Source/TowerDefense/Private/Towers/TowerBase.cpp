// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/TowerBase.h"

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

	if (!towerMeshComponent)
	{
		towerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
		towerMeshComponent->SetupAttachment(RootComponent);
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
	
	for (int i = 0; i < investedResources.Num(); i++)
	{
		investedResources[i] = 0;
	}
}

void ATowerBase::BuildTower()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TowerBase Build Tower"));
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

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATowerBase::Initialize_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TowerBase Initialize implementation"));

	SetActorLocation(FVector(0, 0, 0), false, nullptr, ETeleportType::TeleportPhysics);
	SetActorHiddenInGame(false);

	return true;
}

bool ATowerBase::Disable_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TowerBase Disable implementation"));

	SetActorLocation(FVector(0, 0, -500), false, nullptr, ETeleportType::TeleportPhysics);
	towerMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	ResetTower();

	return true;
}

bool ATowerBase::Activate_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("TowerBase Activate implementation"));
	SetActorLocation(FVector(0, 0, -500), false, nullptr, ETeleportType::TeleportPhysics);
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
