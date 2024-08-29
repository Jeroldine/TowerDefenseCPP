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

	UFUNCTION()
	void SetUpCameraComponent();

	UFUNCTION()
	void SetUpMovementComponent();

	UFUNCTION()
	void SetUpMouseEvents();

	UFUNCTION()
	void SetUpCameraBounds();

	// camera controls
	UFUNCTION()
	void CameraFollow();

	UFUNCTION()
	void ZoomCamera(float Value);

	UFUNCTION()
	void CheckMouseOverActor();

	UFUNCTION()
	void OnMouseClicked();

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
	UFloatingPawnMovement* FloatingPawnMovement;

	// player controller
	UPROPERTY(VisibleAnywhere)
	APlayerController* PC;

	// cached objects that I interact with
	UPROPERTY()
	AActor* currentHoveredOverActor;

	//UPROPERTY()
	// selected tower

	// camera stuff
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float bufferScreenW = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	float bufferScreenH = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float deadZoneWLower = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float deadZoneWUpper = 400.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float deadZoneHLower = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	float deadZoneHUpper = 400.0f;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	FVector minBounds = FVector(-500, 0, 0);

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	FVector maxBounds = FVector(500, 3000, 0);

	// colours
	UPROPERTY(EditDefaultsOnly, Category = Colours)
	FLinearColor defaultColour;

	UPROPERTY(EditDefaultsOnly, Category = Colours)
	FLinearColor highlightColour;

	UPROPERTY(EditDefaultsOnly, Category = Colours)
	FLinearColor buildColour;

	UPROPERTY(EditDefaultsOnly, Category = Colours)
	FLinearColor upgradeColour;

	UPROPERTY(EditDefaultsOnly, Category = Colours)
	FLinearColor destroyColour;
};
