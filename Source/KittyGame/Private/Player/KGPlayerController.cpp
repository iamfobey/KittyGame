// Kitty game project. All rights reserved.

#include "Player/KGPlayerController.h"

#include "EnhancedInputComponent.h"
#include "Player/KGPlayerCameraManager.h"
#include "EnhancedInputSubsystems.h"
#include "Interfaces/KGPlayerControls.h"

AKGPlayerController::AKGPlayerController(): MoveAction(nullptr), LookAction(nullptr), JumpAction(nullptr)
{
	PlayerCameraManagerClass = AKGPlayerCameraManager::StaticClass();
}

void AKGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		// Setup control mappings
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetLocalPlayer()->GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(); InputSubsystem && PlayerMappings.Num() > 0)
		{
			InputSubsystem->ClearAllMappings();
			for (const auto& PlayerMapping : PlayerMappings)
			{
				InputSubsystem->AddMappingContext(PlayerMapping, 0);
			}
		}
	}
}

void AKGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (const auto MoveFunc = FEnhancedInputActionHandlerSignature::TMethodPtr<
			AKGPlayerController>(&ThisClass::Move)) EnhancedInputComponent->BindAction(
			MoveAction, ETriggerEvent::Triggered, this, MoveFunc);
	}
}

void AKGPlayerController::Move(const FInputActionValue& Value) const
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	if (!ControlledPawn->Implements<UKGPlayerControls>()) return;

	IKGPlayerControls::Execute_Move(ControlledPawn, Value.Get<FVector2D>());
}

void AKGPlayerController::Look(const FInputActionValue& Value) const
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	if (!ControlledPawn->Implements<UKGPlayerControls>()) return;

	IKGPlayerControls::Execute_LookAround(ControlledPawn, Value.Get<FVector2D>());
}

void AKGPlayerController::DoJump(const FInputActionValue& Value) const
{
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;

	if (!ControlledPawn->Implements<UKGPlayerControls>()) return;

	if (!Value.Get<bool>()) return;

	IKGPlayerControls::Execute_DoJump(ControlledPawn);
}
