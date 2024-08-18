// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/ColleagueComponent.h"

// Sets default values for this component's properties
UColleagueComponent::UColleagueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UColleagueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UColleagueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UColleagueComponent::SetMediator(TScriptInterface<IMediatorInterface> mediator)
{
	_mediator = mediator;
}

