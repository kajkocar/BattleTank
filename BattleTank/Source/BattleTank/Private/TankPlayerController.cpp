// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	FoundAimingComponent(aimingComponent);
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto screenLocation = FVector2D (ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to world direction
	FVector lookDirection;
	if (GetLookDirection(screenLocation, lookDirection))
	{
		// Line-trace along that look direction and see what we hit (up to max range)
		return GetLookVectorHitLocation(lookDirection, hitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& HitLocation) const
{
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult hitResult;

	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + lookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel( 
			hitResult,
			startLocation,
			endLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = hitResult.Location;
		return true;
	}

	HitLocation = FVector(0, 0, 0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector CameraWorldLocation;	// we do not need camera location
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, CameraWorldLocation, lookDirection);
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }   // if not possesing

	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(aimingComponent)) { return; }

	FVector HitLocation;	// Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		aimingComponent->AimAt(HitLocation);
	}



}



