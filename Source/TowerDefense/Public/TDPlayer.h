// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TDPlayer.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* TDCameraComponent;

	// movement component
	UPROPERTY(VisibleAnywhere)
	UFloatingPawnMovement* movementComponent;

};
