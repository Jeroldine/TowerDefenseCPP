// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/ObjectPoolComponent.h"

// Sets default values for this component's properties
UObjectPoolComponent::UObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Initialize();
}


// Called every frame
void UObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UClass* UObjectPoolComponent::GetObjectClass()
{
	return pooledObjClass;
}

void UObjectPoolComponent::Initialize()
{
	if (pooledObjClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = GetOwner()->GetInstigator();

			for (int i = 0; i < numObjects; i++)
			{
				AActor* obj = World->SpawnActor<AActor>(pooledObjClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);
				IPoolableInterface::Execute_Disable(obj);
				_objects.Add(obj);
			}
		}
	}
	
}

AActor* UObjectPoolComponent::CreateSingleObject()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetOwner()->GetInstigator();

		AActor* obj = World->SpawnActor<AActor>(pooledObjClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParams);
		IPoolableInterface::Execute_Disable(obj);
		_objects.Add(obj);
		return obj;
	}
	return nullptr;
}

AActor* UObjectPoolComponent::SpawnObject()
{
	for (AActor* obj : _objects)
	{
		if (obj->IsHidden())
		{
			IPoolableInterface::Execute_Initialize(obj);
			return obj;
		}
	}

	return CreateSingleObject();
}

