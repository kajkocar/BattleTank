// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 10;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationInDegrees = 40;	// 1000 meters per second
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationInDegrees = 0;	// 1000 meters per second

};
