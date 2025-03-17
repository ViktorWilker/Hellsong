// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HBaseWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponName : uint8
{
	LigthSword UMETA(DisplayName = "LigthSword"),
	Katana UMETA(DisplayName = "Katana")
};

UCLASS()
class HELLSONG_API AHBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AHBaseWeapon();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfos")
	EWeaponName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfos")
	UStaticMeshComponent* StaticWeaponMesh;

private:

};
