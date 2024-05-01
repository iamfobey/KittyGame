// Base game components project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BGCStaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaEmpty);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, NewStamina, float, StaminaDelta);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BASEGAMECOMPONENTS_API UBGCStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBGCStaminaComponent();

	/** Calls when stamina is gone(stamina = 0).*/
	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaEmpty OnStaminaEmpty;

	/** Calls only when stamina changed.*/
	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChanged OnStaminaChanged;

	/** Maximal stamina.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", meta = (ClampMin = "0", UIMin = "0"))
	float MaxStamina = 100.0f;

	/** If true, stamina will "freeze"(won't change).*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	uint8 bFrozen : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	uint8 bAutoRegen : 1;

	/** Delay before start stamina regeneration.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina",
		meta = (EditCondition = "bAutoRegen", ClampMin = "0.01"))
	float StaminaDelay = 5.0f;

	/** Time before full stamina regeneration from 0 to maximum.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina",
		meta = (EditCondition = "bAutoRegen", ClampMin = "0.01"))
	float StaminaRegenTime = 3.0f;

	/** Check on stamina empty.*/
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	FORCEINLINE bool IsEmpty() const { return FMath::IsNearlyZero(Stamina); }

	/** Get current stamina.*/
	UFUNCTION(BlueprintPure, Category = "Stamina")
	FORCEINLINE float GetStamina() const { return Stamina; }

	/** Get current stamina normalized.*/
	UFUNCTION(BlueprintPure, Category = "Stamina")
	FORCEINLINE float GetStaminaNorm() const
	{
		return FMath::GetMappedRangeValueClamped(FVector2D(0.0f, MaxStamina), FVector2D(0.0f, 1.0f), Stamina);
	}

	/** Try to set new stamina.*/
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void SetStamina(const float NewStamina);

	/** Try to set new stamina with normalized value.*/
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	FORCEINLINE void SetStaminaNorm(const float NewStaminaNorm)
	{
		SetStamina(FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(0.0f, MaxStamina),
		                                             FMath::Clamp(NewStaminaNorm, 0.0f, 1.0f)));
	}

	/** Check if stamina full.*/
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	FORCEINLINE float IsStaminaFull() const { return FMath::IsNearlyEqual(Stamina, MaxStamina); }

	/** Set stamina to full.*/
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	FORCEINLINE void RecoverStamina() { SetStamina(MaxStamina); }

protected:
	virtual void BeginPlay() override;
	void StaminaUpdate();

	float Stamina = 0.0f;
	FTimerHandle StaminaTimerHandle;
	float StaminaUpdateTime;
	float StaminaModifier;
	uint8 StaminaRegenFrameRate = 60;
};
