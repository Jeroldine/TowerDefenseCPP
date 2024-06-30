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
	TDCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TDCamera"));
	check(TDCameraComponent != nullptr);
	// Attach the camera component to our root component.
	TDCameraComponent->SetupAttachment(RootComponent);

	//Create Movement component
	movementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
}

// Called when the game starts or when spawned
void ATDPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Using TDPlayer Pawn"));
}

// Called every frame
void ATDPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATDPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

