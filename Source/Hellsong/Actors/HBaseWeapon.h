
#pragma once

#include "CoreMinimal.h"
#include "HBaseEquippable.h"
#include "HBaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponName : uint8
{
	LigthSword UMETA(DisplayName = "LigthSword"),
	Katana UMETA(DisplayName = "Katana")
};

UCLASS()
class HELLSONG_API AHBaseWeapon : public AHBaseEquippable
{
	GENERATED_BODY()

public:
	AHBaseWeapon();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyHitStop(AActor* HitActor, float Duration, float TimeDilation = 0.05f);

protected:
	virtual void BeginPlay() override;

};
