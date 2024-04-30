// Kitty game project. All rights reserved.

#include "Player/KGPlayer.h"

#include "Components/BGCHealthComponent.h"
#include "Components/BGCStaminaComponent.h"
#include "Components/KGCharacterMovementComponent.h"
#include "Interfaces/KGInteraction.h"
#include "Kismet/KismetMathLibrary.h"

AKGPlayer::AKGPlayer(const FObjectInitializer& ObjInit) : Super(
	ObjInit.SetDefaultSubobjectClass<UKGCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bUseControllerRotationYaw = true;

	bWantsToRun = false;

	HealthComponent = CreateDefaultSubobject<UBGCHealthComponent>("HealthComponent");
	StaminaComponent = CreateDefaultSubobject<UBGCStaminaComponent>("StaminaComponent");
}

void AKGPlayer::BeginPlay()
{
	Super::BeginPlay();

	InteractionTraceDelegate.BindUObject(this, &ThisClass::OnInteractionTraceDone);
}

void AKGPlayer::TryMove_Implementation(const FVector2D Value)
{
	IKGPlayerControls::TryMove_Implementation(Value);

	AddMovementInput(
		UKismetMathLibrary::Quat_RotateVector(UE::Math::TQuat(GetActorRotation()), FVector(Value.Y, Value.X, 0.0f)));
}

void AKGPlayer::TryLook_Implementation(const FVector2D Value)
{
	IKGPlayerControls::TryLook_Implementation(Value);

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void AKGPlayer::TryJump_Implementation()
{
	IKGPlayerControls::TryJump_Implementation();

	Jump();
}

void AKGPlayer::TryRun_Implementation(const bool Value)
{
	IKGPlayerControls::TryRun_Implementation(Value);

	bWantsToRun = Value;
}

void AKGPlayer::TryInteract_Implementation(const bool Value)
{
	IKGPlayerControls::TryInteract_Implementation(Value);

	if (!Controller) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FVector TraceStart{};
	FRotator ViewRotation{};

	Controller->GetPlayerViewPoint(TraceStart, ViewRotation);

	const FVector TraceEnd = TraceStart + ViewRotation.Vector() * InteractionTraceDistance;
	FCollisionQueryParams CollisionParams{};
	CollisionParams.AddIgnoredActor(this);
	FCollisionResponseParams ResponseParams{};

	UE_LOG(LogTemp, Display, TEXT("Interaction called"));
	World->AsyncLineTraceByChannel(EAsyncTraceType::Single, TraceStart, TraceEnd, ECC_Visibility, CollisionParams,
	                               ResponseParams, &InteractionTraceDelegate);
}

void AKGPlayer::OnInteractionTraceDone(const FTraceHandle& TraceHandle, FTraceDatum& TraceDatum)
{
	UE_LOG(LogTemp, Display, TEXT("Async LineTrace done"));
	if (TraceDatum.OutHits.Num() <= 0) return;

	AActor* ActorHit = TraceDatum.OutHits[0].GetActor();
	if (!ActorHit) return;

	if (ActorHit->Implements<UKGInteraction>()) IKGInteraction::Execute_Interact(ActorHit, this);
}
