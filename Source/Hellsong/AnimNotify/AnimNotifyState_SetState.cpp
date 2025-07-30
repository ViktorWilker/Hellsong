// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_SetState.h"

#include "Hellsong/ActorComponent/StateManagerComponent.h"

void UAnimNotifyState_SetState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                            float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if(!MeshComp){return;}

	AActor* Owner = MeshComp->GetOwner();
	if(!Owner) {return;}

	if (UStateManagerComponent* StateManager = Owner->FindComponentByClass<UStateManagerComponent>())
	{
		if (bIsState)
		{
			StateManager->SetState(TagToSet);
		}
		else
		{
			StateManager->SetAction(TagToSet);
		}
	}
}

void UAnimNotifyState_SetState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	if (UStateManagerComponent* StateManager = Owner->FindComponentByClass<UStateManagerComponent>())
	{
		if (bIsState)
		{
			StateManager->ResetState();
		}
		else
		{
			StateManager->SetAction(FGameplayTag());
		}
	}
}
