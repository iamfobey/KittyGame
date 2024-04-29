// Kitty game project. All rights reserved.

#include "Player/KGPlayerController.h"

#include "EnhancedInputComponent.h"
#include "Player/KGPlayerCameraManager.h"
#include "EnhancedInputSubsystems.h"
#include "Interfaces/KGPlayerControls.h"

AKGPlayerController::AKGPlayerController(): MoveAction(nullptr), LookAction(nullptr), JumpAction(nullptr),
                                            InteractAction(nullptr)
{
	PlayerCameraManagerClass = AKGPlayerCameraManager::StaticClass();
}

void AKGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		// Setup control mappings
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(); InputSubsystem && PlayerMappings.Num() > 0)
		{
			InputSubsystem->ClearAllMappings();
			for (const auto& PlayerMapping : PlayerMappings)
			{
				InputSubsystem->AddMappingContext(PlayerMapping, 0);
			}
		}
		else
		{
			UE_LOG(LogPlayerController, Warning, TEXT("Can't bind controls! Check PlayerMappings Set."));
		}
	}
}

void AKGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::TryMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::TryLook);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::TryJump);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ThisClass::TryRun);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ThisClass::TryInteract);
	}
	else
	{
		UE_LOG(LogPlayerController, Warning, TEXT("Input component not enhanced. Controls will not working."));
	}
}

void AKGPlayerController::TryMove(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	if (!ControlledPawn->Implements<UKGPlayerControls>()) return;

	IKGPlayerControls::Execute_TryMove(ControlledPawn, Value.Get<FVector2D>());
}

void AKGPlayerController::TryLook(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	if (!ControlledPawn->Implements<UKGPlayerControls>()) return;

	IKGPlayerControls::Execute_TryLook(ControlledPawn, Value.Get<FVector2D>());
}

void AKGPlayerController::TryJump(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	if (!ControlledPawn->Implements<UKGPlayerControls>()) return;

	if (!Value.Get<bool>()) return;

	IKGPlayerControls::Execute_TryJump(ControlledPawn);
}

void AKGPlayerController::TryRun(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	if (!ControlledPawn->Implements<UKGPlayerControls>()) return;

	IKGPlayerControls::Execute_TryRun(ControlledPawn, Value.Get<bool>());
}

void AKGPlayerController::TryInteract(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	if (!ControlledPawn->Implements<UKGPlayerControls>()) return;

	if (!Value.Get<bool>()) return;

	IKGPlayerControls::Execute_TryInteract(ControlledPawn);
}
