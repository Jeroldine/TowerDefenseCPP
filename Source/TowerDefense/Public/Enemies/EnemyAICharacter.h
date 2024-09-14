// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Helpers/HealthComponent.h"
#include "Helpers/PoolableInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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

	UPROPERTY(EditDefaultsOnly)
	float moveSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly)
	TArray<int> possibleTerrains;

	UPROPERTY(VisibleAnywhere)
	int currentTerrain = 0;

	UPROPERTY(EditAnywhere)
	TArray<FVector> pathPoints;

	UPROPERTY(EditDefaultsOnly)
	int currentPathIndex = 0;

	///////////////
	// Functions //
	///////////////

	UFUNCTION()
	void ResetBehaviorTree();

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
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void RequestNewPath();

	// IPoolableInterface functions
	bool Initialize_Implementation() override;

	bool Disable_Implementation() override;

	bool Activate_Implementation() override;
};
