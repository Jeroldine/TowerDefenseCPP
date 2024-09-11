// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyTasks/BTT_GetNextLocation.h"

EBTNodeResult::Type UBTT_GetNextLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	navArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (navArea)
	{
		AEnemyAICharacter* AICharacter = Cast<AEnemyAICharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (AICharacter)
		{
			nextLocation = AICharacter->GetNextPointOnPath();
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("NextDestination"), nextLocation);

	return EBTNodeResult::Succeeded;
}
