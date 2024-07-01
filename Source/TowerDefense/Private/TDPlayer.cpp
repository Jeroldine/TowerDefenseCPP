// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayer.h"

// Sets default values
ATDPlayer::ATDPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerSceneComponent"));
	}

	// Create a TD camera component.
	SetUpCameraComponent();

	//Create Movement component
	SetUpMovementComponent();
}

// Called when the game starts or when spawned
void ATDPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Using TDPlayer Pawn"));

	// show cursor and enable mouse events
	SetUpMouseEvents();
	SetUpCameraBounds();
}

void ATDPlayer::SetUpCameraComponent()
{
	TDCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TDCamera"));
	check(TDCameraComponent != nullptr);
	// Attach the camera component to our root component.
	TDCameraComponent->SetupAttachment(RootComponent);
}

void ATDPlayer::SetUpMovementComponent()
{
	if (!FloatingPawnMovement)
	{
		FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
		FloatingPawnMovement->UpdatedComponent = RootComponent;
	}
}

void ATDPlayer::SetUpMouseEvents()
{
	PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}

void ATDPlayer::SetUpCameraBounds()
{
	int32 ScreenW, ScreenH;
	PC->GetViewportSize(ScreenW, ScreenH);

	deadZoneWLower = ScreenW * (0.5f - bufferScreenW);
	deadZoneWUpper = ScreenW * (0.5f + bufferScreenW);

	deadZoneHLower = ScreenH * (0.5f - bufferScreenH);
	deadZoneHUpper = ScreenH * (0.5f + bufferScreenH);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("ViewPort size: X=%d, Y=%d"), ScreenW, ScreenH));
}

// Called every frame
void ATDPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CameraFollow();
}

// Called to bind functionality to input
void ATDPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// Set up zoom bindings
	PlayerInputComponent->BindAxis("ZoomCamera", this, &ATDPlayer::ZoomCamera);
}

void ATDPlayer::CameraFollow()
{
	FVector actorLoc = GetActorLocation();

	if (PC)
	{
		float MouseX, MouseY;
		if (PC->GetMousePosition(MouseX, MouseY))
		{
			// Print the mouse position to the screen for debugging
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Mouse Position: X=%f, Y=%f"), MouseX, MouseY));
			FVector directionW = GetActorRightVector();
			FVector directionH = GetActorForwardVector();

			if (MouseX > deadZoneWUpper)
			{
				FloatingPawnMovement->AddInputVector(directionW);
			}
			if (MouseX < deadZoneWLower)
			{
				FloatingPawnMovement->AddInputVector(-directionW);
			}
			if (MouseY > deadZoneHUpper)
			{
				FloatingPawnMovement->AddInputVector(-directionH);
			}
			if (MouseY < deadZoneHLower)
			{
				FloatingPawnMovement->AddInputVector(directionH);
			}
			// Clamp actor position within bounds
			actorLoc.X = FMath::Clamp(actorLoc.X, minBounds.X, maxBounds.X);
			actorLoc.Y = FMath::Clamp(actorLoc.Y, minBounds.Y, maxBounds.Y);
			SetActorLocation(actorLoc);
		}
	}
}

void ATDPlayer::ZoomCamera(float Value)
{
	FVector direction = TDCameraComponent->GetForwardVector();
	AddMovementInput(direction, Value);
}

