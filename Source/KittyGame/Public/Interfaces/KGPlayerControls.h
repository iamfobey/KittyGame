// Kitty game project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/Interface.h"
#include "KGPlayerControls.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UKGPlayerControls : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KITTYGAME_API IKGPlayerControls
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Blueprintable, BlueprintNativeEvent, Category="Player Controls")
	void TryMove(const FVector2D Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Player Controls")
	void TryLook(const FVector2D Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Player Controls")
	void TryJump();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Player Controls")
	void TryRun(const bool Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Player Controls")
	void TryInteract(const bool Value);
};
