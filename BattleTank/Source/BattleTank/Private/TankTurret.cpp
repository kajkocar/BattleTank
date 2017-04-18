// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	// move the barrel the right amount this frame
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, +1.0f);
	auto elevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto newRotation = RelativeRotation.Yaw + elevationChange;

	SetRelativeRotation(FRotator(0, newRotation, 0));

	// given a max elevation speed and the frame time

}



