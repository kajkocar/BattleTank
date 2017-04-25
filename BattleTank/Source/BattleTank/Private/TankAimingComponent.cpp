// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	Barrel = barrelToSet;
	Turret = turretToSet;
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("Ticking"));
	if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSeconds)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (isBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}

}

bool UTankAimingComponent::isBarrelMoving()
{
	if (!Barrel || !Turret)
		return false;

	auto barrelForward = Barrel->GetForwardVector();

	return !barrelForward.Equals(AimDirection, 0.01);
}


void UTankAimingComponent::MoveBarrelTowards()
{
	if (!Barrel || !Turret)
		return;

	// work out difference between current barrel rotation and aim direction
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = AimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	if (deltaRotator.Yaw < 180)
	{
		Turret->Rotate(deltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-deltaRotator.Yaw);
	}

}

void UTankAimingComponent::AimAt(FVector worldSpaceLoc)
{
	if (!Barrel || !Turret)
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}

}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringStatus::Reloading)
	{
		// spawn projectile on the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}
