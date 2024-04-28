// Kitty game project. All rights reserved.

#include "CoreLogic/KGGameModeBase.h"

#include "Player/KGPlayer.h"
#include "Player/KGPlayerController.h"
#include "Player/KGPlayerState.h"

AKGGameModeBase::AKGGameModeBase()
{
	DefaultPawnClass = AKGPlayer::StaticClass();
	PlayerControllerClass = AKGPlayerController::StaticClass();
	PlayerStateClass = AKGPlayerState::StaticClass();
}
