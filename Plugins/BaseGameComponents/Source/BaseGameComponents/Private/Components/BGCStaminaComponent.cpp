// Base game components project. All rights reserved.

#include "Components/BGCStaminaComponent.h"

UBGCStaminaComponent::UBGCStaminaComponent(): bFrozen(false), bAutoRegen(true)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	StaminaUpdateTime = 1.0f / static_cast<float>(StaminaRegenFrameRate);
	StaminaModifier = MaxStamina / (StaminaRegenTime * StaminaRegenFrameRate);
}

void UBGCStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	SetStamina(MaxStamina);
}

void UBGCStaminaComponent::StaminaUpdate()
{
	SetStamina(Stamina + StaminaModifier);

	if (const UWorld* World = GetWorld(); IsStaminaFull() && World)
		World->GetTimerManager().ClearTimer(
			StaminaTimerHandle);
}

void UBGCStaminaComponent::SetStamina(const float NewStamina)
{
	if (FMath::IsNearlyEqual(NewStamina, Stamina)) return;

	const float NextStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
	const float StaminaDelta = NextStamina - Stamina;

	Stamina = NextStamina;
	OnStaminaChanged.Broadcast(Stamina, StaminaDelta);

	if (IsEmpty()) OnStaminaEmpty.Broadcast();

	if (const UWorld* World = GetWorld(); World && Stamina < MaxStamina)
		World->GetTimerManager().SetTimer(
			StaminaTimerHandle, this, &ThisClass::StaminaUpdate, StaminaUpdateTime, true, StaminaDelay);
}
