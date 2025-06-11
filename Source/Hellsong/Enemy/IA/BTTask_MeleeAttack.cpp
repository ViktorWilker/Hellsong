// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = "MeleeAttack";
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if(OutOfRange)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	auto const * const cont = OwnerComp.GetAIOwner();
	auto* const enemy = Cast<ABaseEnemy>(cont->GetPawn());

	if(auto* const icombat = Cast<IAICombatInterface>(enemy))
	{
		if(MontageHasFinished(enemy))
		{
				icombat->Execute_MeleeAttack(enemy);
		}
	}

	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	
}

bool UBTTask_MeleeAttack::MontageHasFinished(ABaseEnemy* const enemy)
{
	return enemy->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(enemy->GetMontage());
}
