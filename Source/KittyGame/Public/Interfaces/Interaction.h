// Kitty game project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interaction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KITTYGAME_API IInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	bool Interact(AActor* Causer);
};
