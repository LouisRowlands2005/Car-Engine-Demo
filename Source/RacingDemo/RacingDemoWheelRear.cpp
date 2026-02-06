// Copyright Epic Games, Inc. All Rights Reserved.

#include "RacingDemoWheelRear.h"
#include "UObject/ConstructorHelpers.h"

URacingDemoWheelRear::URacingDemoWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}