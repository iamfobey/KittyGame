// Base game components project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BGCHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, NewHealth, float, HealthDelta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBarriersChangedSignature, uint8, NewBarriers, uint8, BarriersDelta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChangedSignature, int32, Value);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BASEGAMECOMPONENTS_API UBGCHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBGCHealthComponent();

	/** Calls when component owner is dead(health = 0).*/
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeathSignature OnDeath;

	/** Calls only when health changed.*/
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChangedSignature OnHealthChanged;

	/** Calls only when barriers changed.*/
	UPROPERTY(BlueprintAssignable, Category="Protection")
	FOnBarriersChangedSignature OnBarriersChanged;

	/** If true, health will "freeze"(damage will not apply, not working if damage is pure).*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	uint8 bImmortal : 1;

	/** Maximum health.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0"))
	float MaxHealth = 100.0f;

	/** Maximum Barriers.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Protection")
	uint8 MaxBarriers = 0;

	/** Check on death.*/
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE bool IsDead() const { return FMath::IsNearlyZero(Health); }

	/** Get current health.*/
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetHealth() const { return Health; }

	/** Get current barriers.*/
	UFUNCTION(BlueprintPure, Category = "Protection")
	FORCEINLINE uint8 GetBarriers() const { return Barriers; }

protected:
	virtual void BeginPlay() override;

	float Health = 0.0f;
	uint8 Barriers = 0;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                     AController* InstigatedBy, AActor* DamageCauser);

	void SetHealth(const float NewHealth);
	void SetBarriers(const uint8 NewBarriers);
};
