// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankTrack;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* barrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* turretToSet);
	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetLeftTrack(UTankTrack* trackToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetRightTrack(UTankTrack* trackToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = Setup)
		UTankAimingComponent* tankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Setup)
		UTankMovementComponent* tankMovementComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float reloadTimeInSeconds = 3;

	UTankBarrel* Barrel = nullptr;

	double lastFireTime = 0;

	UTankTrack* trackLeft;
	UTankTrack* trackRight;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
