// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Hellsong/Structs/SBaseStat.h"
#include "StatsComponent.generated.h"

UENUM(BlueprintType)
enum class EStats : uint8
{
	None UMETA(DisplayName = "Name"),
	Health UMETA(DisplayName = "Health"),
	Mana UMETA(DisplayName = "Mana"),
	Sanctification UMETA(DisplayName = "Sanctification"),
	Corruption UMETA(DisplayName = "Corruption"),
	Balance UMETA(DisplayName = "Balance")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChangedSignature, EStats, StatType, float, NewValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELLSONG_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatsComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void InitializeStats();

	UFUNCTION(BlueprintCallable)
	void ModifyCurrentStatValue(EStats stat, float value, bool bShoudRegen);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float InDamage);

	UFUNCTION()
	void HandleDelayedRegen(EStats Stat);
	
	UFUNCTION(BlueprintCallable)
	void StartRegen(EStats StatType);
	
	UFUNCTION()
	void RegenStat(EStats Stat);
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentStatValue(EStats Stat, float value);

	UFUNCTION(BlueprintCallable)
	void SetBaseStatValue(EStats Stat, float value);

	UFUNCTION(BlueprintCallable)
	void SetMaxStatValue(EStats Stat, float value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetRegenRate(EStats stat) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentStatValue(EStats Stat);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetBaseStatValue(EStats Stat);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxStatValue(EStats Stat);
	
	UPROPERTY(EditAnywhere, Category = "BaseStats")
	TMap<EStats, FBaseStat> BaseStats;

	UPROPERTY(BlueprintAssignable, Category="Stats")
	FOnStatChangedSignature OnStatChanged;
	
	
protected:
	virtual void BeginPlay() override;
	FTimerHandle RegenTimerHandle;
	
private:
	TMap<EStats, float> CurrentStatValue;
	TMap<EStats, FTimerHandle> RegenTimerHandles;
	TMap<EStats, FTimerHandle> RegenDelayHandles;
	bool bCanRegenerate = false;
	float ManaRegenRate = 2.f;
};
