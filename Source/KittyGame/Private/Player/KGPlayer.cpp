// Kitty game project. All rights reserved.

#include "Player/KGPlayer.h"

AKGPlayer::AKGPlayer()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AKGPlayer::Move_Implementation(const FVector2D Value)
{
	IKGPlayerControls::Move_Implementation(Value);

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (!MovementComponent) return;
}

void AKGPlayer::BeginPlay()
{
	Super::BeginPlay();
}
