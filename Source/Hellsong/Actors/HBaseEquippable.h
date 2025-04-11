// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HBaseEquippable.generated.h"

UCLASS()
class HELLSONG_API AHBaseEquippable : public AActor
{
	GENERATED_BODY()
	
public:	
	AHBaseEquippable();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UPrimitiveComponent* GetItemMesh();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnEquipped();
	virtual void OnEquipped_Implementation();
	
	UFUNCTION(BlueprintCallable)
	void OnUnequipped();

	UFUNCTION(BlueprintCallable)
	void SetEquipped(bool value);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsEquipped();
	
	UFUNCTION(BlueprintCallable)
	void AttachActor(FName SocketName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equippable")
	FName EquipedSocket;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category=Character, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> ItemSkeletalMesh;

	UPROPERTY(Category=Character, EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ItemStaticMesh;

	bool bIsEquipped;
	
};
