// Fill out your copyright notice in the Description page of Project Settings.


#include "StateManagerComponent.h"

UStateManagerComponent::UStateManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UStateManagerComponent::SetAction(FGameplayTag NewAction)
{
	if(NewAction == CurrentCharacterAction) {return;}

	if(CurrentCharacterAction.IsValid())
	{
		OnActionEnded.Broadcast(CurrentCharacterAction);
	}

	CurrentCharacterAction = NewAction;

	if(NewAction.IsValid())
	{
		OnActionBegin.Broadcast(NewAction);
	}
}

void UStateManagerComponent::SetState(FGameplayTag NewState)
{
	
	if(NewState == CurrentState) {return;}

	if(CurrentState.IsValid())
	{
		OnStateEnded.Broadcast(CurrentState);
	}
	
	CurrentState = NewState;

	if(NewState.IsValid())
	{
		OnStateBegin.Broadcast(NewState);
	}
}

void UStateManagerComponent::ResetState()
{
	CurrentState = FGameplayTag::RequestGameplayTag(FName("Character.State.Idle"));
}

FName UStateManagerComponent::GetCurrentState()
{
	return CurrentState.GetTagName();
}

FGameplayTag UStateManagerComponent::GetCurrentAction()
{
	return CurrentCharacterAction;
}

bool UStateManagerComponent::IsCurrentStateEqualToSAny(FGameplayTagContainer StatesToCheck)
{
	return StatesToCheck.HasTag(CurrentState);
}

bool UStateManagerComponent::IsCurrentActionEqualToSAny(FGameplayTagContainer ActionsToCheck)
{
	return ActionsToCheck.HasTag(CurrentCharacterAction);
}





