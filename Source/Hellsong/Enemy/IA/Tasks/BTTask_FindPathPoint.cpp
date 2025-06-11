// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPathPoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Hellsong/Enemy/IA/Enemy_AIController.h"

UBTTask_FindPathPoint::UBTTask_FindPathPoint(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Path Point";
}

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AEnemy_AIController* const cont = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		if(UBlackboardComponent* const bc = OwnerComp.GetBlackboardComponent())
		{
			int const index = bc->GetValueAsInt(GetSelectedBlackboardKey());

			if(ABaseEnemy* enemy = Cast<ABaseEnemy>(cont->GetPawn()))
			{
				auto const PathPoint = enemy->GetPatrolPath()->GetPatrolPoint(index);

				auto const GlobalPoint = enemy->GetPatrolPath()->GetActorTransform().TransformPosition(PathPoint);
				bc->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName, GlobalPoint);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
