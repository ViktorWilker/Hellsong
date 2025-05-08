#pragma once
#include "CoreMinimal.h"
#include "SBaseStat.generated.h"

USTRUCT(BlueprintType)
struct FBaseStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxValue;

	FBaseStat()
		: BaseValue(0), MaxValue(0){}
};
