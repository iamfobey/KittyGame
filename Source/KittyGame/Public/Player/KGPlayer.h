// Kitty game project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/KGPlayerControls.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "KGPlayer.generated.h"

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
		return bWantsToRun && !GetVelocity().IsZero();
	}

	virtual void TryMove_Implementation(const FVector2D Value) override;
	virtual void TryLook_Implementation(const FVector2D Value) override;
	virtual void TryJump_Implementation() override;
	virtual void TryRun_Implementation(const bool Value) override;
	virtual void TryInteract_Implementation(const bool Value) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBGCHealthComponent* HealthComponent;
	
	uint8 bWantsToRun : 1;

	virtual void BeginPlay() override;
};
