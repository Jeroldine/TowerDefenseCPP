// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayer.h"
#include "DrawDebugHelpers.h"
#include "Helpers/InteractableInterface.h"

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
	CheckMouseOverActor();
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
				//FloatingPawnMovement->AddInputVector(directionW);
				AddMovementInput(directionW);
			}
			if (MouseX < deadZoneWLower)
			{
				//FloatingPawnMovement->AddInputVector(-directionW);
				AddMovementInput(-directionW);
			}
			if (MouseY > deadZoneHUpper)
			{
				//FloatingPawnMovement->AddInputVector(-directionH);
				AddMovementInput(-directionH);
			}
			if (MouseY < deadZoneHLower)
			{
				//FloatingPawnMovement->AddInputVector(directionH);
				AddMovementInput(directionH);
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

void ATDPlayer::CheckMouseOverActor()
{
	// Get the mouse position
	float MouseX, MouseY;
	if (PC->GetMousePosition(MouseX, MouseY))
	{
		FVector WorldLocation, WorldDirection;
		// Convert screen position to world space direction
		if (PC->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection))
		{
			FVector Start = WorldLocation;
			FVector End = Start + (WorldDirection * 10000.0f); // Line trace distance

			FHitResult HitResult;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(PC->GetPawn()); // Ignore the player itself

			// Perform the line trace
			if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
			{
				AActor* hitActor = HitResult.GetActor();
				IInteractableInterface* interactInterface = Cast<IInteractableInterface>(hitActor);

				if (hitActor && interactInterface) // check if the actor I hit has the InteractableInterface
				{
					if (hitActor != currentHoveredOverActor)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()));


						currentHoveredOverActor = hitActor;
						IInteractableInterface::Execute_OnHoverStart(currentHoveredOverActor);
					}

					
					
					
				}
				else // actor does not have the interface
				{
					currentHoveredOverActor = nullptr;
				}
			}
			else // didn't hit anything
			{
				currentHoveredOverActor = nullptr;
			}
		}
	}
}

void ATDPlayer::OnMouseClicked()
{

}

ATowerBase* ATDPlayer::RetrieveTower(UClass*)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("asking for tower"));
	return nullptr;
}

bool ATDPlayer::GetInBuildMode()
{
	return inBuildMode;
}

bool ATDPlayer::GetInDestroyMode()
{
	return inDestroyMode;
}

void ATDPlayer::EnterBuildMode()
{
	SetModes(true, false);

}

void ATDPlayer::EnterDestroyMode()
{
	SetModes(false, true);
	ReturnTower();
}

void ATDPlayer::ExitAllModes()
{
	SetModes(false, false);
	ReturnTower();
}

void ATDPlayer::SetModes(bool buildMode, bool destroyMode)
{
	inBuildMode = buildMode;
	inDestroyMode = destroyMode;
}

void ATDPlayer::ReturnTower()
{
	if (selectedTower)
	{
		// disable tower
		selectedTower = nullptr;
	}
}

