// Kitty game project. All rights reserved.

#include "Player/KGPlayer.h"

#include "Kismet/KismetMathLibrary.h"

AKGPlayer::AKGPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bUseControllerRotationYaw = true;
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

void AKGPlayer::TryPush_Implementation()
{
	IKGPlayerControls::TryPush_Implementation();
}