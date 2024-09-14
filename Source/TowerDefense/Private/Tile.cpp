// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TileSceneComponent"));
	}*/

	if (!boxComponent)
	{
		boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
		//boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFortress::BeginOverlap);
		//boxComponent->InitBoxExtent(FVector(150.0f, 100.0f, 100.0f));
		RootComponent = boxComponent;
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FIntPoint ATile::GetGridPos()
{
	return gridPos;
}

void ATile::SetGridPos(int row, int col)
{
	gridPos.X = row;
	gridPos.Y = col;
}

void ATile::Initialize(int row, int col, float targetSideLength)
{
	if (!tileMeshComponent)
	{
		tileMeshComponent = FindComponentByClass<UStaticMeshComponent>();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Got tile mesh component."));
	}

	// set gridPos
	gridPos.X = row;
	gridPos.Y = col;

	//adjust tile size
	float xExtent = tileMeshComponent->GetStaticMesh()->GetBounds().BoxExtent.X;
	float originalLength = 2 * xExtent;
	float newScale = (targetSideLength / originalLength) * shrinkFactor;

	tileMeshComponent->SetRelativeScale3D(FVector(newScale, newScale, 1));

	float newXExtent = (targetSideLength / 2.0f) * shrinkFactor;
	boxComponent->InitBoxExtent(FVector(newXExtent, newXExtent, newXExtent));
}

void ATile::SetMaterialInstance(UMaterial* masterMaterial)
{
	if (tileMeshComponent && masterMaterial)
	{
		tileMaterialInstance = UMaterialInstanceDynamic::Create(masterMaterial, this);
		tileMaterialInstance->GetVectorParameterValue(FName("BaseColor"), defaultColor); // gets starting colour
		tileMeshComponent->SetMaterial(0, tileMaterialInstance);
	}
}

void ATile::SetMaterialColor(FLinearColor newColor)
{
	tileMaterialInstance->SetVectorParameterValue(FName("BaseColor"), newColor);
}

int ATile::GetNumOccupants()
{
	return occupantsMap.Num();
}

void ATile::AddOccupant(AActor* newOccupant)
{
	FString actorName;
	newOccupant->GetName(actorName);

	occupantsMap.Add(actorName, newOccupant);
}

void ATile::RemoveOccupant(AActor* leavingOccupant)
{
	FString actorName;
	leavingOccupant->GetName(actorName);
	occupantsMap.Remove(actorName);
}

void ATile::SetCanBuildOn(bool canBuild)
{
	canBuildOn = canBuild;
}

bool ATile::GetCanBuildOn()
{
	return canBuildOn;
}

bool ATile::CheckForTowerOccupant()
{
	TArray<FString> keyArray;
	occupantsMap.GenerateKeyArray(keyArray);

	for (FString key : keyArray)
	{
		if (Cast<ATowerBase>(*occupantsMap.Find(key)))
		{
			return true;
		}
	}
	return false;
}

bool ATile::CheckForEnemyOccupant()
{
	TArray<FString> keyArray;
	occupantsMap.GenerateKeyArray(keyArray);

	for (FString key : keyArray)
	{
		if (Cast<AEnemyAICharacter>(*occupantsMap.Find(key)))
		{
			return true;
		}
	}
	return false;
}

void ATile::ResetActor()
{
	canBuildOn = true;
	
	occupantsMap.Empty(3);

	tileMaterialInstance->SetVectorParameterValue(FName("BaseColor"), defaultColor);
}

TArray<FIntPoint> ATile::GetNeighbors()
{
	return neighborsArray;
}

void ATile::SetNeighbors(int maxRows, int maxCols)
{
	if (gridPos.X - 1 > 0) // if tile below is valied
		neighborsArray.Add(FIntPoint(gridPos.X - 1, gridPos.Y));

	if (gridPos.X + 1 < maxRows) // if tile above is valid
		neighborsArray.Add(FIntPoint(gridPos.X + 1, gridPos.Y));

	if (gridPos.Y - 1 > 0) // if tile to left is valid
		neighborsArray.Add(FIntPoint(gridPos.X, gridPos.Y - 1));

	if (gridPos.Y + 1 < maxCols) // if tile to right is valid
		neighborsArray.Add(FIntPoint(gridPos.X, gridPos.Y + 1));
}

void ATile::OnClick_Implementation()
{
	
}

void ATile::OnHoverStart_Implementation()
{
	
}

void ATile::OnHoverStop_Implementation()
{
	tileMaterialInstance->SetVectorParameterValue(FName("BaseColor"), defaultColor);
}
