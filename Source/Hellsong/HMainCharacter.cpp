#include "HMainCharacter.h"

AHMainCharacter::AHMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

