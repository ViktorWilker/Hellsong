
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
	
protected:
	virtual void BeginPlay() override;

};
