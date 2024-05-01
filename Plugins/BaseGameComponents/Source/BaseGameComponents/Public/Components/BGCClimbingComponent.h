// Base game components project. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BGCClimbingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCanClimbChange, bool, CanClimbing);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartClimbing);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopClimbing);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFoundClimbingSurface, FHitResult, SurfaceHitResult);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BASEGAMECOMPONENTS_API UBGCClimbingComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UBGCClimbingComponent();

	UPROPERTY(BlueprintAssignable)
	FOnCanClimbChange OnCanClimbChange;

	UPROPERTY(BlueprintAssignable)
	FOnStartClimbing OnStartClimbing;

	UPROPERTY(BlueprintAssignable)
	FOnStopClimbing OnStopClimbing;

	UPROPERTY(BlueprintAssignable)
	FOnFoundClimbingSurface OnFoundClimbingSurface;

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsClimbing() const { return bCanClimb && bWantsToClimb; }

	/** If true, the owner will hit the surface as soon as the opportunity arises.*/
	UFUNCTION(BlueprintCallable)
	void SetWantsToClimb(const bool WantsToClimb);

protected:
	UPROPERTY(BlueprintReadOnly)
	uint8 bWantsToClimb : 1;

	UPROPERTY(BlueprintReadOnly)
	uint8 bCanClimb : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ClimbDistance = 60.0f;

	/** Owner can climb only if surface actor has special tag.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 bClimbByTag : 1;

	/** Special surface actor climb tag.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bClimbByTag"))
	FName ClimbTag = TEXT("climb");

	/** Number of traces to check climb surface per second.*/
	UPROPERTY(EditAnywhere)
	uint8 CheckFrameRate = 10;

	FTimerHandle CheckTimerHandle;
	float CheckTick;
	FTraceDelegate CheckTraceDelegate;

	virtual void BeginPlay() override;
	virtual void DestroyComponent(bool bPromoteChildren) override;

	void OnCheckTraceDone(const FTraceHandle& TraceHandle, FTraceDatum& TraceDatum);
	void OnCheckTraceFail();
	void OnCheckTraceComplete();
	void Climbing(FHitResult& SurfaceHitResult);
};
