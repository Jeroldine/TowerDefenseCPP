// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Helpers/PoolableInterface.h"
#include "ObjectPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPoolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	///////////////
	// variables //
	///////////////
	UPROPERTY(EditDefaultsOnly, meta = (MustImplement = "IPoolableInterface"))
	TSubclassOf<AActor> pooledObjClass;

	UPROPERTY(EditDefaultsOnly)
	int numObjects = 10;

	/*UPROPERTY()
	TArray<TScriptInterface<IPoolableInterface>> _objects;*/

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void SetObjectClass(UClass* objClass);



	//void Initialize();
};
