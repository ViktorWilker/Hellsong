

#include "HBaseWeapon.h"

#include "GameFramework/Character.h"


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

void AHBaseWeapon::ApplyHitStop(AActor* HitActor, float Duration, float TimeDilation)
{
	if (ACharacter* HitCharacter = Cast<ACharacter>(HitActor))
	{
		HitCharacter->CustomTimeDilation = TimeDilation; 
        
		FTimerHandle HitStopTimer;
		GetWorldTimerManager().SetTimer(HitStopTimer, [HitCharacter]()
		{
			HitCharacter->CustomTimeDilation = 1.0f; 
		}, Duration, false);
	}
}
