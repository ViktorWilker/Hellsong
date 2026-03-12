// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "StateManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateBegin, FGameplayTag, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateEnded, FGameplayTag, State);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionBegin, FGameplayTag, NewAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionEnded, FGameplayTag, Action);

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HELLSONG_API UStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStateManagerComponent();

	UFUNCTION(BlueprintCallable)
	void SetAction(FGameplayTag NewAction);
	
	UFUNCTION(BlueprintCallable)
	void SetState(FGameplayTag NewState);

	UFUNCTION(BlueprintCallable)
	void ResetState();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetCurrentState() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetCurrentAction() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCurrentStateEqualToSAny(FGameplayTagContainer StatesToCheck);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCurrentActionEqualToSAny(FGameplayTagContainer ActionsToCheck);
		
	UPROPERTY(BlueprintAssignable, Category = "State")
	FOnStateBegin OnStateBegin;
	
	UPROPERTY(BlueprintAssignable, Category = "State")
	FOnStateEnded OnStateEnded;
	
	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnActionEnded OnActionEnded;
	
	UPROPERTY(BlueprintAssignable, Category = "Action")
	FOnActionBegin OnActionBegin;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FGameplayTag CurrentState;
	FGameplayTag CurrentCharacterAction;

};
