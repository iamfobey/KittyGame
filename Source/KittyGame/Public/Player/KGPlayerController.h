// Kitty game project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "KGPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class KITTYGAME_API AKGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AKGPlayerController();

protected:
	// Input
	// ------------------------------------------------------------
	/** Main player mapping context with all supported actions.*/
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TSet<UInputMappingContext*> PlayerMappings;

	UPROPERTY(EditDefaultsOnly, Category="Input|Supported Actions")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input|Supported Actions")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Input|Supported Actions")
	UInputAction* JumpAction;
	// ------------------------------------------------------------

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value) const;
	void Look(const FInputActionValue& Value) const;
	void DoJump(const FInputActionValue& Value) const;
};
