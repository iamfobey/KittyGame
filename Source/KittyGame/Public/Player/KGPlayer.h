// Kitty game project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/KGPlayerControls.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "KGPlayer.generated.h"

class UBGCClimbingComponent;
class UCameraComponent;
class UBGCStaminaComponent;
class UBGCHealthComponent;

UCLASS()
class KITTYGAME_API AKGPlayer : public ACharacter, public IKGPlayerControls
{
	GENERATED_BODY()

public:
	AKGPlayer(const FObjectInitializer& ObjInit);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FORCEINLINE bool IsMoving() const
	{
		return !GetVelocity().IsZero() && !GetCharacterMovement()->IsFalling();
	}

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FORCEINLINE bool IsRunning() const
	{
		return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
	}

	virtual void TryMove_Implementation(const FVector2D Value) override;
	virtual void TryLook_Implementation(const FVector2D Value) override;
	virtual void TryJump_Implementation() override;
	virtual void TryRun_Implementation(const bool Value) override;
	virtual void TryInteract_Implementation(const bool Value) override;
	virtual void TryClimb_Implementation(const bool Value) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Head;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Paw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBGCClimbingComponent* ClimbingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBGCHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBGCStaminaComponent* StaminaComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractionTraceDistance = 75.0f;

	uint8 bWantsToRun : 1;
	uint8 bIsMovingForward : 1;
	FTraceDelegate InteractionTraceDelegate;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnInteract();

	void OnInteractionTraceDone(const FTraceHandle& TraceHandle, FTraceDatum& TraceDatum);

	virtual void BeginPlay() override;
};
