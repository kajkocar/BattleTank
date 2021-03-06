// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move the barrel the right amount this frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, +1.0f);
	auto elevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = FMath::Clamp<float>(RelativeRotation.Pitch + elevationChange, MinElevationInDegrees, MaxElevationInDegrees);
	
	SetRelativeRotation(FRotator(rawNewElevation, 0, 0));

	// given a max elevation speed and the frame time

}


