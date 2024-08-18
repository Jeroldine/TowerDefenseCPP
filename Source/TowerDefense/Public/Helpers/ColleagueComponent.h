// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Helpers/MediatorInterface.h"
#include "ColleagueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UColleagueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColleagueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TScriptInterface<IMediatorInterface> _mediator;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMediator(TScriptInterface<IMediatorInterface> mediator);
};
