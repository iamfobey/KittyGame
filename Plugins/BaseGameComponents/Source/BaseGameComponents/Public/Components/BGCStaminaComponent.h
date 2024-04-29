// Base game components project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BGCStaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASEGAMECOMPONENTS_API UBGCStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBGCStaminaComponent();

protected:
	virtual void BeginPlay() override;		
};
