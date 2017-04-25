// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum UE4 way so he can see it
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class AProjectile;
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector worldSpaceLoc);
	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringState = EFiringStatus::Reloading;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float reloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	
	FVector AimDirection;
	bool isBarrelMoving();

	void MoveBarrelTowards();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	double lastFireTime = 0;


};
