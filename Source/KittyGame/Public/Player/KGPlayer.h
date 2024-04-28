// Kitty game project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/KGPlayerControls.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "KGPlayer.generated.h"

UCLASS()
class KITTYGAME_API AKGPlayer : public ACharacter, public IKGPlayerControls
{
	GENERATED_BODY()

public:
	AKGPlayer();
	virtual void Move_Implementation(const FVector2D Value) override;

protected:
	virtual void BeginPlay() override;
};
