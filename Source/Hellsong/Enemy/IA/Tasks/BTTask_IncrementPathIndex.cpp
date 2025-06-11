// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncrementPathIndex.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Hellsong/Enemy/IA/Enemy_AIController.h"

UBTTask_IncrementPathIndex::UBTTask_IncrementPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Increment Path Index";
}

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AEnemy_AIController* const cont = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		if(auto* const enemy = Cast<ABaseEnemy>(cont->GetPawn()))
		{
			if(auto* const bc = OwnerComp.GetBlackboardComponent())
			{
				auto const NoOfPoints = enemy->GetPatrolPath()->Num();
				auto const MinIndex = 0;
				auto const MaxIndex = NoOfPoints - 1;
				auto index = bc->GetValueAsInt(GetSelectedBlackboardKey());

				if(bBidirectional)
				{
					if(index >= MaxIndex && Direction == EDirectionType::Forward)
					{
						Direction = EDirectionType::Reverse;
					}
					else if (index == MinIndex && Direction == EDirectionType::Reverse)
					{
						Direction = EDirectionType::Forward;
					}
				}

				bc->SetValueAsInt(GetSelectedBlackboardKey(), (Direction == EDirectionType::Forward ? ++index : --index) % NoOfPoints);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
