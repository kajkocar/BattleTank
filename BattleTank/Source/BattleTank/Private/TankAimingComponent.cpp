// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
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

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// work out difference between current barrel rotation and aim direction
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = AimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
}

void UTankAimingComponent::AimAt(FVector worldSpaceLoc, float LaunchSpeed)
{
	if (!Barrel)
		return;

//	UE_LOG(LogTemp, Warning, TEXT("UTankAimingComponent::AimAt %s"), *worldSpaceLoc.ToString());

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
// 		auto Time = GetWorld()->GetTimeSeconds();
// 		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution find"), Time);
	}
	else
	{
// 		auto Time = GetWorld()->GetTimeSeconds();
// 		UE_LOG(LogTemp, Warning, TEXT("%f: No Aim solve find"), Time);
	}


	/*
	auto barrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *ourTankName, *worldSpaceLoc.ToString(), *barrelLocation.ToString());
*/

}
