// Fill out your copyright notice in the Description page of Project Settings.


#include "HBaseWeapon.h"

AHBaseWeapon::AHBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	StaticWeaponMesh->SetupAttachment(RootComponent);
}

void AHBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

