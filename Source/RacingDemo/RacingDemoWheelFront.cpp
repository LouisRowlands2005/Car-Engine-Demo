// Copyright Epic Games, Inc. All Rights Reserved.

#include "RacingDemoWheelFront.h"
#include "UObject/ConstructorHelpers.h"

URacingDemoWheelFront::URacingDemoWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}