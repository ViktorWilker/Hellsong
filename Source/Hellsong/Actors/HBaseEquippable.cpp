// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseEquippable.h"

#include "GameFramework/Character.h"

AHBaseEquippable::AHBaseEquippable()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ItemSkeletalMesh =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	ItemStaticMesh =  CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	ItemSkeletalMesh->SetupAttachment(RootComponent);
	ItemStaticMesh->SetupAttachment(RootComponent);
}

void AHBaseEquippable::BeginPlay()
{
	Super::BeginPlay();
	
}

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

void AHBaseEquippable::OnEquipped_Implementation()
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

