// Fill out your copyright notice in the Description page of Project Settings.


#include "Towers/Projectile.h"
#include "Enemies/EnemyAICharacter.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 1000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	InitialLifeSpan = 1.5f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyAICharacter* enemy = Cast<AEnemyAICharacter>(OtherActor);
	if (enemy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("EnemyHit"));
		enemy->TakeHit(damageAmount);
		Destroy();
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& ShootDirection, float dmg)
{
	damageAmount = dmg;
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

