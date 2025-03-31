// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseEquippable.h"

#include "GameFramework/Character.h"

AHBaseEquippable::AHBaseEquippable()
{
	PrimaryActorTick.bCanEverTick = true;
	ItemSkeletalMesh =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	ItemStaticMesh =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

void AHBaseEquippable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHBaseEquippable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* AHBaseEquippable::GetItemMesh()
{
	if(ItemStaticMesh->GetStaticMesh())
	{
		return ItemStaticMesh;
	}
	else
	{
		return ItemSkeletalMesh;
	}
}

void AHBaseEquippable::OnEquipped()
{
	SetEquipped(true);
	AttachActor(AttachSocketName);
}

void AHBaseEquippable::OnUnequipped()
{
	if(bIsEquipped)
	{
		SetEquipped(false);	
	}
}

void AHBaseEquippable::SetEquipped(bool value)
{
	bIsEquipped = value;
}

bool AHBaseEquippable::IsEquipped()
{
	return bIsEquipped;
}

void AHBaseEquippable::AttachActor(FName SocketName)
{
	ACharacter* character = Cast<ACharacter>(GetOwner());
	if(character)
	{
		USkeletalMeshComponent* Mesh = character->GetMesh();
		if(Mesh)
		{
			AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
		}
	}
}

