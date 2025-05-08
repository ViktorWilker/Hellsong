// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UStatsComponent::InitializeStats()
{
	for(const TPair<EStats, FBaseStat>& Elem : BaseStats)
	{
		SetCurrentStatValue(Elem.Key,Elem.Value.BaseValue);
	}
}

void UStatsComponent::SetCurrentStatValue(EStats Stat, float value)
{
	CurrentStatValue.Add(Stat, value);
}

float UStatsComponent::GetCurrentStatValue(EStats Stat)
{
	return *CurrentStatValue.Find(Stat);
}

