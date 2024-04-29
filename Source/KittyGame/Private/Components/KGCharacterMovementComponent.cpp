// Kitty game project. All rights reserved.


#include "Components/KGCharacterMovementComponent.h"

#include "Player/KGPlayer.h"

float UKGCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AKGPlayer* Player = Cast<AKGPlayer>(GetPawnOwner());

	return Player && Player->IsRunning() && !IsFalling() ? MaxSpeed * RunModifier : MaxSpeed;
}
