// Kitty game project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KGInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKGInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KITTYGAME_API IKGInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * @param Causer Interacted actor.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	bool Interact(AActor* Causer);
};
