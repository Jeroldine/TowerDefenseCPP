// Fill out your copyright notice in the Description page of Project Settings.

#include "Fortress.h"
#include "GUI/TowerDefenseHUD.h"
#include "Enemies/EnemyAICharacter.h"
#include "GUI/Menus/GameMenuWidget.h"

// Sets default values
AFortress::AFortress()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!boxComponent)
	{
		boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
		boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFortress::BeginOverlap);
		boxComponent->InitBoxExtent(FVector(150.0f, 100.0f, 100.0f));
		RootComponent = boxComponent;
	}

	if (!healthComponent)
	{
		healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	}

	

}

// Called when the game starts or when spawned
void AFortress::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AFortress::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

void AFortress::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnOverlap(OtherActor);
}

void AFortress::OnOverlap(AActor* OtherActor)
{
	// if OtherActor is of type AEnemyAICharacter
	// decrease health -> checks if dead
	// update healthBar

	AEnemyAICharacter* enemy = Cast<AEnemyAICharacter>(OtherActor);

	if (!enemy) return;

	if (healthComponent->GetHealth() > 0)
	{
		healthComponent->DecreaseHealth(enemy->GetDamageAmount());

		// disable enemy
		//IPoolableInterface::Execute_Disable(enemy);

		// update healthbar
		UGameMenuWidget* gameMenu = Cast<UGameMenuWidget>(UGameplayStatics::GetActorOfClass(this, UGameMenuWidget::StaticClass()));
		if (gameMenu)
		{
			gameMenu->UpdateHealthBar(healthComponent->GetNormalizedHealth());
		}

		// check if dead
		if (healthComponent->GetHealth() <= 0)
		{
			EndGame();
		}
	}
	else
	{
		// disable enemy
		//IPoolableInterface::Execute_Disable(enemy);
	}
}



void AFortress::EndGame()
{
	// update HUD
	ATowerDefenseHUD* TDHUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<ATowerDefenseHUD>();
	if (TDHUD) TDHUD->ShowGameOverMenu();

	// call game mode End game
}

void AFortress::StartGamePlay()
{
	isAlive = true;
}

void AFortress::ResetActor()
{
}

void AFortress::UpdatePlayerHUD()
{
	ATowerDefenseHUD* TDHUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<ATowerDefenseHUD>();
	if (TDHUD)
	{
		
	}

	UGameMenuWidget* gameMenu = Cast<UGameMenuWidget>(UGameplayStatics::GetActorOfClass(this, UGameMenuWidget::StaticClass()));
	if (gameMenu)
	{
		gameMenu->UpdateHealthBar(healthComponent->GetNormalizedHealth());
	}
}

//void AFortress::DamageSelf(float dt)
//{
//	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Fortress Damaged Self"));
//	healthComponent->DecreaseHealth(dt * 10.0f);
//	UGameMenuWidget* gameMenu = Cast<UGameMenuWidget>(UGameplayStatics::GetActorOfClass(this, UGameMenuWidget::StaticClass()));
//	if (gameMenu)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Update healthBar"));
//		gameMenu->UpdateHealthBar(healthComponent->GetNormalizedHealth());
//	}
//}

