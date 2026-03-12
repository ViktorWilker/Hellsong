#include "HMainCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AHMainCharacter::AHMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	StateManager = CreateDefaultSubobject<UStateManagerComponent>(TEXT("StateManager"));
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	SetupStimulusSource();
}

void AHMainCharacter::SetIsSptinting(bool value)
{
	bIsSprinting = value;
}

void AHMainCharacter::SetIsDead(bool value)
{
	bIsDead = value;
}

bool AHMainCharacter::IsDead()
{
	return bIsDead;
}

void AHMainCharacter::ApplyHitStop(AActor* HitActor, float Duration)
{
	if (ACharacter* HitCharacter = Cast<ACharacter>(HitActor))
	{
		HitCharacter->CustomTimeDilation = 0.05f; 
        
		FTimerHandle HitStopTimer;
		GetWorldTimerManager().SetTimer(HitStopTimer, [HitCharacter]()
		{
			HitCharacter->CustomTimeDilation = 1.0f; 
		}, Duration, false);
	}
}

void AHMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AHMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const float InputMagnitude = MovementInput.Size();
	float TargetSpeed = 0.f;

	if(InputMagnitude > KINDA_SMALL_NUMBER)
	{
		TargetSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
	}

	GetCharacterMovement()->MaxWalkSpeed = FMath::FInterpTo(
		GetCharacterMovement()->MaxWalkSpeed, 
		TargetSpeed, 
		DeltaTime, 
		InterpSpeed
	);

	MovementInput = FVector::ZeroVector;
}

void AHMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHMainCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHMainCharacter::Look);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AHMainCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AHMainCharacter::StopSprint);
		

	}
}

bool AHMainCharacter::IsSprinting()
{
	return bIsSprinting;
}

void AHMainCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		MovementInput = FVector(MovementVector.X, MovementVector.Y, 0.f);
	}
}

void AHMainCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHMainCharacter::StartSprint()
{
	bIsSprinting = true;
	UE_LOG(LogTemp, Error, TEXT("Sprint Started!"));
}

void AHMainCharacter::StopSprint()
{
	bIsSprinting = false;
	UE_LOG(LogTemp, Error, TEXT("Sprint Stoped!"));
}

void AHMainCharacter::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if(StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}
