// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (!leftTrackToSet || !rightTrackToSet)
		return;

	leftTtrack = leftTrackToSet;
	rightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
//	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward Throw: %f"), Throw);

	leftTtrack->SetThrottle(Throw);
	rightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	//	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward Throw: %f"), Throw);

	leftTtrack->SetThrottle(Throw);
	rightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	//	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward Throw: %f"), Throw);

	leftTtrack->SetThrottle(-Throw);
	rightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
// 	auto tankName = GetOwner()->GetName();
// 	UE_LOG(LogTemp, Warning, TEXT("%s: RequestDirectMove: %s %c"), *tankName, *MoveVelocity.ToString(), (bForceMaxSpeed ? 'Y' : 'N') );

	// we only need directions, we will move the tank
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto forwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(forwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

}
