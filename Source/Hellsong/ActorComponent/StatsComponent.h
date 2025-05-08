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
	Corruption UMETA(DisplayName = "Corruption")
};

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
	void SetCurrentStatValue(EStats Stat, float value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentStatValue(EStats Stat);

	UPROPERTY(EditAnywhere, Category = "BaseStats")
	TMap<EStats, FBaseStat> BaseStats;
	
protected:
	virtual void BeginPlay() override;

private:
	TMap<EStats, float> CurrentStatValue; 
};
