// Base game components project. All rights reserved.

#include "Components/BGCHealthComponent.h"

#include "DamageTypes/PureDamage.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UBGCHealthComponent::UBGCHealthComponent() : bImmortal(false)
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UBGCHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
	SetBarriers(MaxBarriers);

	if (AActor* Owner = GetOwner()) Owner->OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnTakeAnyDamage);
	else UE_LOG(LogHealthComponent, Warning, TEXT("Can't assign on owner's take damage. Owner not found"))
}

void UBGCHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                          AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	// Check if pure damage
	if (Cast<UPureDamage>(DamageType))
	{
		SetHealth(Health - Damage);
		return;
	}

	if (bImmortal) return;

	if (Barriers > 0)
	{
		SetBarriers(Barriers - 1);
		return;
	}

	SetHealth(Health - Damage);
}

void UBGCHealthComponent::SetHealth(const float NewHealth)
{
	if (FMath::IsNearlyEqual(NewHealth, Health)) return;

	const float NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const float HealthDelta = NextHealth - Health;

	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);

	if (IsDead()) OnDeath.Broadcast();
}

void UBGCHealthComponent::SetBarriers(const uint8 NewBarriers)
{
	const uint8 NextBarriers = FMath::Clamp(NewBarriers, static_cast<uint8>(0), MaxBarriers);
	const uint8 BarriersDelta = NextBarriers - Barriers;

	Barriers = NextBarriers;
	OnBarriersChanged.Broadcast(Barriers, BarriersDelta);
}
