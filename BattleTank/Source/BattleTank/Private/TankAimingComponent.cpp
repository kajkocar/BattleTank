// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	Barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
	Turret = turretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// work out difference between current barrel rotation and aim direction
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = AimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	Turret->Rotate(deltaRotator.Yaw);
}

void UTankAimingComponent::AimAt(FVector worldSpaceLoc, float LaunchSpeed)
{
	if (!Barrel)
		return;

	if (!Turret)
		return;

	FVector OutLaunchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));
	// calculate OutLaunchVelocity

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		startLocation,
		worldSpaceLoc,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if ( bHaveAimSolution )
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

}
