// Kitty game project. All rights reserved.

#include "Player/KGPlayer.h"

#include "Components/BGCHealthComponent.h"
#include "Components/KGCharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

AKGPlayer::AKGPlayer(const FObjectInitializer& ObjInit) : Super(
	ObjInit.SetDefaultSubobjectClass<UKGCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bUseControllerRotationYaw = true;

	bWantsToRun = false;

	HealthComponent = CreateDefaultSubobject<UBGCHealthComponent>("HealthComponent");
}

void AKGPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AKGPlayer::TryMove_Implementation(const FVector2D Value)
{
	IKGPlayerControls::TryMove_Implementation(Value);

	AddMovementInput(
		UKismetMathLibrary::Quat_RotateVector(UE::Math::TQuat(GetActorRotation()), FVector(Value.Y, Value.X, 0.0f)));
}

void AKGPlayer::TryLook_Implementation(const FVector2D Value)
{
	IKGPlayerControls::TryLook_Implementation(Value);

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void AKGPlayer::TryJump_Implementation()
{
	IKGPlayerControls::TryJump_Implementation();

	Jump();
}

void AKGPlayer::TryRun_Implementation(const bool Value)
{
	IKGPlayerControls::TryRun_Implementation(Value);

	bWantsToRun = Value;
}

void AKGPlayer::TryInteract_Implementation()
{
	IKGPlayerControls::TryInteract_Implementation();
}
