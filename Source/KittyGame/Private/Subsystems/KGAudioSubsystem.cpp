// Kitty game project. All rights reserved.


#include "Subsystems/KGAudioSubsystem.h"
#include "Components/AudioComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAudioSys, All, All);

void UKGAudioSubsystem::PlayLevelAmbient(UAudioComponent* WorldAmbient,
                                         const TSet<TSoftObjectPtr<USoundBase>> CurrentLevelAmbient,
                                         const float VolumeNorm)
{
	AudioComponent = WorldAmbient;
	if (!AudioComponent) return;

	// Volume settings
	BaseAudioVolume = AudioComponent->VolumeMultiplier;
	SetAmbientVolume(VolumeNorm);

	AudioComponent->OnAudioFinished.AddDynamic(this, &ThisClass::CycleAmbient);

	if (LevelAmbient.Num() > 0)
	{
		LevelAmbient.Empty();
		Indexes.Init(false, LevelAmbient.Num());
	}

	LevelAmbient = CurrentLevelAmbient;

	CycleAmbient();
}

void UKGAudioSubsystem::SetAmbientVolume(const float VolumeNorm) const
{
	if (!AudioComponent) return;

	AudioComponent->SetVolumeMultiplier(FMath::Clamp(BaseAudioVolume * VolumeNorm, 0.001f, 1.0f));
}

void UKGAudioSubsystem::CycleAmbient()
{
	if (!GetWorld()) return;

	int32 CurrentIndex;

	if (Indexes.Num() != LevelAmbient.Num() || Indexes.CountSetBits() == Indexes.Num())
		Indexes.Init(
			false, LevelAmbient.Num());

	if (LevelAmbient.Num() == 0)
	{
		UE_LOG(LogAudioSys, Warning, TEXT("Ambient not found"));
		return;
	}

	do
	{
		CurrentIndex = FMath::RandRange(0, LevelAmbient.Num() - 1);
	}
	while (Indexes[CurrentIndex]);
	Indexes[CurrentIndex] = true;

	auto SoundIt = LevelAmbient.CreateIterator();
	for (int32 i = 0; i < CurrentIndex; ++i)
	{
		++SoundIt;
	}

	USoundBase* Song = SoundIt->LoadSynchronous();
	if (!Song) return;

	AudioComponent->SetSound(Song);
	AudioComponent->Play();
	// UE_LOG(LogAudioSys, Display, TEXT("Ok %s"), *Song->GetName())
}
