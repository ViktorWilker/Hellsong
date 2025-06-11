// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_ChangeSpeed.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Hellsong/Enemy/BaseEnemy.h"

UBTService_ChangeSpeed::UBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = "Change Speed";
}

void UBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if(AAIController* const cont = OwnerComp.GetAIOwner())
	{
		if(ABaseEnemy* const enemy = Cast<ABaseEnemy>(cont->GetPawn()))
		{
			enemy->GetCharacterMovement()->MaxWalkSpeed = speed;
		}
	}
}
