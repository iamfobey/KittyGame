// Kitty game project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KGCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class KITTYGAME_API UKGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement",
		meta = (ClampMin = "1.1", ClampMax = "10", UIMin = "1.1", UIMax = "10"))
	float RunModifier = 2.0f;

	virtual float GetMaxSpeed() const override;
};
