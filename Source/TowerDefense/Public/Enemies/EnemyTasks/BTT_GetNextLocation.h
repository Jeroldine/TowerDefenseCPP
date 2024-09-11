// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/EnemyAIController.h"
#include "Enemies/EnemyAICharacter.h"
#include "BTT_GetNextLocation.generated.h"

//#include "NavigationSystem.h"
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBTT_GetNextLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	FVector nextLocation;
	UNavigationSystemV1* navArea;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
