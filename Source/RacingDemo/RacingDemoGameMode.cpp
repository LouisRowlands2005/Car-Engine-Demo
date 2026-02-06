// Copyright Epic Games, Inc. All Rights Reserved.

#include "RacingDemoGameMode.h"
#include "RacingDemoPlayerController.h"

ARacingDemoGameMode::ARacingDemoGameMode()
{
	PlayerControllerClass = ARacingDemoPlayerController::StaticClass();
}
