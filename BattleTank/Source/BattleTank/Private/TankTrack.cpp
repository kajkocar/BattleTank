// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float throttle)
{
// 	auto Time = GetWorld()->GetTimeSeconds();
// 	auto Name = GetName();
// 	UE_LOG(LogTemp, Warning, TEXT("%s: SetThrottle %f"), *Name, throttle);

	auto forceApplied = GetForwardVector() * throttle * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	
	// owner of track is tank body, just what we need
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


