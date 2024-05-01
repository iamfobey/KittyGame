// Kitty game project. All rights reserved.

#include "Player/KGPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/BGCClimbingComponent.h"
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
	bIsMovingForward = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	Head = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	Head->SetupAttachment(Camera);

	Paw = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	Paw->SetupAttachment(RootComponent);

	ClimbingComponent = CreateDefaultSubobject<UBGCClimbingComponent>("ClimbingComponent");
	ClimbingComponent->SetupAttachment(RootComponent);

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

	const FVector Origin = ClimbingComponent && ClimbingComponent->IsClimbing()
		                       ? FVector(0.0f, Value.X, Value.Y)
		                       : FVector(Value.Y, Value.X, 0.0f);

	const FVector Movement = UKismetMathLibrary::Quat_RotateVector(UE::Math::TQuat(GetActorRotation()), Origin);

	if (Value.Y > 0) bIsMovingForward = true;
	else bIsMovingForward = false;

	AddMovementInput(Movement);
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

	World->AsyncLineTraceByChannel(EAsyncTraceType::Single, TraceStart, TraceEnd, ECC_Visibility, CollisionParams,
	                               FCollisionResponseParams(), &InteractionTraceDelegate);
}

void AKGPlayer::TryClimb_Implementation(const bool Value)
{
	IKGPlayerControls::TryClimb_Implementation(Value);

	if (ClimbingComponent) ClimbingComponent->SetWantsToClimb(Value);
}

void AKGPlayer::OnInteractionTraceDone(const FTraceHandle& TraceHandle, FTraceDatum& TraceDatum)
{
	if (TraceDatum.OutHits.Num() <= 0) return;

	AActor* ActorHit = TraceDatum.OutHits[0].GetActor();
	if (!ActorHit) return;

	if (ActorHit->Implements<UKGInteraction>())
	{
		IKGInteraction::Execute_Interact(ActorHit, this);

		// Blueprint implementation
		OnInteract();
	}
}
