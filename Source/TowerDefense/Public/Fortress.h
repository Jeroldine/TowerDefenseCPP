// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Helpers/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Helpers/PoolableInterface.h"
#include "Fortress.generated.h"

UCLASS()
class TOWERDEFENSE_API AFortress : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFortress();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UHealthComponent* healthComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* boxComponent;

	UPROPERTY(EditDefaultsOnly)
	bool isAlive = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlap(AActor* OtherActor);

	UFUNCTION()
	void EndGame();

	UFUNCTION()
	void StartGamePlay();

	UFUNCTION()
	void ResetActor();

	void TestDamage(float dt);

	UFUNCTION()
	void UpdatePlayerHUD();
};
