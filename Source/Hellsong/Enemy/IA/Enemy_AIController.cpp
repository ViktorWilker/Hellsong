// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_AIController.h"

AEnemy_AIController::AEnemy_AIController(FObjectInitializer const& ObjectInitializer)
{
}

void AEnemy_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(ABaseEnemy* const Enemy = Cast<ABaseEnemy>(InPawn))
	{
		if(UBehaviorTree* const tree = Enemy->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
