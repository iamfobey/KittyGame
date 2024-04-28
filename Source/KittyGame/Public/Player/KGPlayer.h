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
	virtual void TryMove_Implementation(const FVector2D Value) override;
	virtual void TryLook_Implementation(const FVector2D Value) override;
	virtual void TryJump_Implementation() override;
	virtual void TryPush_Implementation() override;

protected:
	virtual void BeginPlay() override;
};
