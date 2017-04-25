// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"     // must be last include

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* aimingCompRef);

private:
	// Start the tank moving barrel so that a shot would hit where
	// the crosshai intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hitLocation) const;
	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;
	bool GetLookVectorHitLocation(FVector lookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.25f;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0f;   // 10km - 1000000 cm

};
