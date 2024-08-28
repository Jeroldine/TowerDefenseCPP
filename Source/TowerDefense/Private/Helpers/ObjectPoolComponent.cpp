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
	
}


// Called every frame
void UObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectPoolComponent::SetObjectClass(UClass* objClass)
{
	if (objClass->ImplementsInterface(UPoolableInterface::StaticClass()))
	{
		pooledObjClass = objClass;
	}
}

//void UObjectPoolComponent::Initialize()
//{
//	if (pooledObjClass)
//	{
//		UWorld* World = GetWorld();
//		if (World)
//		{
//			FActorSpawnParameters SpawnParams;
//			SpawnParams.Owner = GetOwner();
//			SpawnParams.Instigator = GetOwner()->GetInstigator();
//
//			TScriptInterface<IPoolableInterface>* tower = World->SpawnActor<TScriptInterface<IPoolableInterface>>(pooledObjClass, FVector(0, 0, -500), FRotator(0, 0, 0), SpawnParams);
//		}
//	}
//	
//}

