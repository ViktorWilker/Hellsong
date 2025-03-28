

#include "HBaseWeapon.h"


AHBaseWeapon::AHBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AHBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

