// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

int ABaseEnemy::MeleeAttack_Implementation()
{
	if(Montage)
	{
		PlayAnimMontage(Montage);
	}
	return IAICombatInterface::MeleeAttack_Implementation();
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseEnemy::SetIsDead(bool value)
{
	bIsDead = value;
}

bool ABaseEnemy::IsDead()
{
	return bIsDead;
}

UBehaviorTree* ABaseEnemy::GetBehaviorTree() const
{
	return Tree;
}

APatrolPath* ABaseEnemy::GetPatrolPath() const
{
	return PatrolPath;
}

UAnimMontage* ABaseEnemy::GetMontage() const
{
	return Montage;
}

