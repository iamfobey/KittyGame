// Base game components project. All rights reserved.

#include "Components/BGCStaminaComponent.h"

UBGCStaminaComponent::UBGCStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UBGCStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
}
