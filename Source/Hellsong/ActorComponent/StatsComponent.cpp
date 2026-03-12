#include "StatsComponent.h"

#include "StateManagerComponent.h"
#include "TimerManager.h"

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

void UStatsComponent::ModifyCurrentStatValue(EStats stat, float value, bool bShoudRegen)
{
	if(value == 0) return;
	
	float l_value = GetCurrentStatValue(stat) + value;
	float clampvalue = FMath::Clamp(l_value, 0.f, GetMaxStatValue(stat));
	SetCurrentStatValue(stat, clampvalue);
	if(bShoudRegen)
	{
		HandleDelayedRegen(stat);
	}
}

void UStatsComponent::TakeDamage(float InDamage)
{
	if (InDamage == 0.f) return;
	if (GetCurrentStatValue(EStats::Health) <= 0)
	{
		if (const auto statecomp = GetOwner()->FindComponentByClass<UStateManagerComponent>())
		{
			statecomp->SetState(FGameplayTag::RequestGameplayTag("Character.State.Dead"));
			return;
		}
	}
	ModifyCurrentStatValue(EStats::Health,InDamage * -1.0f, false);
}

void UStatsComponent::HandleDelayedRegen(EStats Stat)
{
	GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandles.FindOrAdd(Stat));
	GetWorld()->GetTimerManager().ClearTimer(RegenDelayHandles.FindOrAdd(Stat));
	
	FTimerDelegate DelayDelegate;
	DelayDelegate.BindUObject(this, &UStatsComponent::StartRegen, Stat);

	GetWorld()->GetTimerManager().SetTimer(
		RegenDelayHandles[Stat],
		DelayDelegate,
		1.0f,
		false
	);
}

void UStatsComponent::StartRegen(EStats StatType)
{
	FTimerDelegate RegenDelegate;
	RegenDelegate.BindUObject(this, &UStatsComponent::RegenStat, StatType);

	GetWorld()->GetTimerManager().SetTimer(
		RegenTimerHandles[StatType],
		RegenDelegate,
		0.1f,
		true
	);
}

void UStatsComponent::RegenStat(EStats Stat)
{
	
	float Current = GetCurrentStatValue(Stat);
	float Max = GetMaxStatValue(Stat);
	if (Current >= Max)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandles[Stat]);
		return;
	}

	float RegenAmount = GetRegenRate(Stat);
	Current = FMath::Min(Current + RegenAmount, Max);
	SetCurrentStatValue(Stat, Current);
}


void UStatsComponent::SetCurrentStatValue(EStats Stat, float value)
{
	CurrentStatValue.FindOrAdd(Stat) = value;
	OnStatChanged.Broadcast(Stat, value);
}

void UStatsComponent::SetBaseStatValue(EStats Stat, float value)
{
	if(FBaseStat* statstruct = BaseStats.Find(Stat))
	{
		statstruct->BaseValue = value;
	}
}

void UStatsComponent::SetMaxStatValue(EStats Stat, float value)
{
	if(FBaseStat* statstruct = BaseStats.Find(Stat))
	{
		statstruct->MaxValue = value;
	}
}

float UStatsComponent::GetRegenRate(EStats stat) const
{
	switch (stat)
	{
	case EStats::Mana:
		return ManaRegenRate;
		default:
			return 0.f;
	}
}

float UStatsComponent::GetCurrentStatValue(EStats Stat)
{
	return *CurrentStatValue.Find(Stat);
}

float UStatsComponent::GetBaseStatValue(EStats Stat)
{
	return BaseStats.Find(Stat)->BaseValue;
}

float UStatsComponent::GetMaxStatValue(EStats Stat)
{
	return BaseStats.Find(Stat)->MaxValue;
}

