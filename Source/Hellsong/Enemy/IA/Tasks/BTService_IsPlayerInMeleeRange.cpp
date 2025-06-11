// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInMeleeRange.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Hellsong/Enemy/IA/Enemy_AIController.h"
#include "Kismet/GameplayStatics.h"

UBTService_IsPlayerInMeleeRange::UBTService_IsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = "Is Player In Melee Range";
}

void UBTService_IsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(AEnemy_AIController* const cont = Cast<AEnemy_AIController>(OwnerComp.GetAIOwner()))
	{
		if(ABaseEnemy* const enemy = Cast<ABaseEnemy>(cont->GetPawn()))
		{
			auto const * const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), enemy->GetDistanceTo(player) <= MeleeRange);
		}
	}
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}
