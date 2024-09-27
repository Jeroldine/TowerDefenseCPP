// Fill out your copyright notice in the Description page of Project Settings.


#include "TDPlayer.h"
#include "DrawDebugHelpers.h"
#include "Helpers/InteractableInterface.h"
#include "GUI/Menus/GameMenuWidget.h"

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

	// Set up player click binding
	PlayerInputComponent->BindAction("MouseClick", IE_Pressed, this, &ATDPlayer::StorePressedActor);
	PlayerInputComponent->BindAction("MouseClick", IE_Released, this, &ATDPlayer::ChooseMouseClickAction);
}

void ATDPlayer::StorePressedActor()
{
	if (currentHoveredOverActor)
		pressedActor = currentHoveredOverActor;
}

void ATDPlayer::ChooseMouseClickAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Mouse click released"));
	// if not hovering over anthing clicking won't do anything
	if (!currentHoveredOverActor) return;

	// if hovering over a tile with a selected tower and clicking the tile -> see if you can build
	if (selectedTower)
	{
		ATile* pressedTile = Cast<ATile>(pressedActor);
		ATile* hoveredTile = Cast<ATile>(currentHoveredOverActor);

		// check if pressed actor and hovered actor are both tiles, and the same tile, and can build on it and no occupants
		if ((hoveredTile && pressedTile) && (hoveredTile == pressedTile) && hoveredTile->GetCanBuildOn() && hoveredTile->GetNumOccupants() == 0)
			if (CheckMaterialRequirement(selectedTower->GetMaterialReqs()) && inBuildMode) // check if enough resources
			{
				UpdateMaterials(selectedTower->GetMaterialReqs().arr);
				hoveredTile->AddOccupant(selectedTower);
				IPoolableInterface::Execute_Activate(selectedTower);
				// update grid manager data
				AGridManager* gridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(this, AGridManager::StaticClass()));
				gridManager->UpdatePlacementAndDamageMaps(selectedTower->GetGridPos(), selectedTower->GetTargetableTypes(), 
					selectedTower->GetAttackRange(), selectedTower->GetAttackPower());
				selectedTower = nullptr;
			}
	}

	else // if hovering over a tower with no selected tower and click -> destroy tower
	{
		ATowerBase* pressedTower = Cast<ATowerBase>(pressedActor);
		ATowerBase* hoveredTower = Cast<ATowerBase>(currentHoveredOverActor);
		if ((hoveredTower && pressedTower) && (hoveredTower == pressedTower) && inDestroyMode)
		{
			UpdateMaterials(hoveredTower->RecoverMaterials(), true);
			// remove occupant from tile
			ATile* tileUnderTower = RequestTile(hoveredTower->GetGridPos());
			tileUnderTower->RemoveOccupant(hoveredTower);
			IPoolableInterface::Execute_Disable(hoveredTower);
			// update grid manager data
			AGridManager* gridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(this, AGridManager::StaticClass()));
			gridManager->UpdatePlacementAndDamageMaps(hoveredTower->GetGridPos(), hoveredTower->GetTargetableTypes(), 
				hoveredTower->GetAttackRange(), hoveredTower->GetAttackPower(), false);
		}
	}
	pressedActor = nullptr;
}

bool ATDPlayer::CheckMaterialRequirement(FLevelRequirements materialReqs)
{
	for (int i = 0; i < currentMaterials.Num(); i++)
	{
		if (currentMaterials[i] < materialReqs[i])
			return false;
	}
	return true;
}

void ATDPlayer::UpdateMaterials(TArray<int> incomingMatls, bool AddMaterials)
{
	if (AddMaterials)
	{
		for (int i = 0; i < currentMaterials.Num(); i++)
			currentMaterials[i] += incomingMatls[i];
	}
	else
	{
		for (int i = 0; i < currentMaterials.Num(); i++)
			currentMaterials[i] -= incomingMatls[i];
	}

	ATowerDefenseHUD* TDHUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<ATowerDefenseHUD>();
	if (TDHUD)
	{
		UGameMenuWidget* gameMenu = Cast<UGameMenuWidget>(TDHUD->currentMenu);
		if (gameMenu)
			gameMenu->UpdateMaterialsText(currentMaterials);
	}
}

void ATDPlayer::HandleMouseOver(AActor* hitActor)
{
	if (currentHoveredOverActor)
	{
		IInteractableInterface::Execute_OnHoverStop(currentHoveredOverActor);
		if (Cast<ATowerBase>(currentHoveredOverActor))
		{
			ATowerBase* hoveredTower = Cast<ATowerBase>(currentHoveredOverActor);
			ATile* tileUnderTower = RequestTile(hoveredTower->GetGridPos());
			IInteractableInterface::Execute_OnHoverStop(tileUnderTower);
		}
	}
		
	// hover over logic
	currentHoveredOverActor = hitActor;
	IInteractableInterface::Execute_OnHoverStart(currentHoveredOverActor);

	if (Cast<ATile>(currentHoveredOverActor)) // always change tile colour
	{
		ATile* currentTile = Cast<ATile>(currentHoveredOverActor);

		currentTile->SetMaterialColor(ChooseTileColor(currentTile)); // might move into GridManager

		if (selectedTower) // in build mode trying to build tower
		{
			selectedTower->SetActorLocation(currentHoveredOverActor->GetActorLocation());
			selectedTower->SetGridPos(currentTile->GetGridPos());
			// flood fill to determine if can build
			OnCheckForValidPath.Broadcast(currentTile->GetGridPos(), selectedTower->GetTargetableTypes());
		}
	}
	else if (Cast<ATowerBase>(currentHoveredOverActor))
	{
		ATowerBase* hoveredTower = Cast<ATowerBase>(currentHoveredOverActor);
		if (!hoveredTower->GetIsPlaced()) return;
		ATile* tileUnderTower = RequestTile(hoveredTower->GetGridPos());
		tileUnderTower->SetMaterialColor(ChooseTileColor(tileUnderTower));
	}
}

ATile* ATDPlayer::RequestTile(FIntPoint pos)
{
	AGridManager* gridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(this, AGridManager::StaticClass()));
	return gridManager->GetTileAtPos(pos);
}

void ATDPlayer::UpdateGridManagerData()
{
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
					if (hitActor != currentHoveredOverActor) // only do something if the hit actor is different than current 
					{
						//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()));
						
						HandleMouseOver(hitActor);
					}					
				}
				else // actor does not have the interface
				{
					if (currentHoveredOverActor)
						IInteractableInterface::Execute_OnHoverStop(currentHoveredOverActor);

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

FLinearColor ATDPlayer::ChooseTileColor(ATile* tile)
{
	if (!tile) return FLinearColor();

	if (inBuildMode) 
	{
		if (tile->GetCanBuildOn() && tile->GetNumOccupants() == 0) // blue if can build on tile and no occupants
			return buildColour;
		else
			return destroyColour; // red if can't build or occupants		
	}
	else if (inDestroyMode)
	{
		if (tile->CheckForTowerOccupant()) // red if building in occupants
			return destroyColour;
		else
			return highlightColour; // white if no building in occupants 
	}
	else
	{
		if (tile->CheckForTowerOccupant()) // orange if tower
			return upgradeColour;
		else
			return highlightColour; // white if no tower
	}

	return FLinearColor();
}

void ATDPlayer::RetrieveTower(UClass* towerClass)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("asking for tower"));

	ReturnTower();

	ATowerManager* towerManager = Cast<ATowerManager>(UGameplayStatics::GetActorOfClass(this, ATowerManager::StaticClass()));
	selectedTower = Cast<ATowerBase>(towerManager->RequestTower(towerClass));
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
		IPoolableInterface::Execute_Disable(selectedTower);
		selectedTower = nullptr;
	}
}

void ATDPlayer::ResetActor(TArray<int> startingMatls)
{
	currentMaterials = { 0, 0, 0, 0 };
	UpdateMaterials(startingMatls, true);
	currentHoveredOverActor = nullptr;
	selectedTower = nullptr;
	pressedActor = nullptr;
	SetModes(false, false);
}

