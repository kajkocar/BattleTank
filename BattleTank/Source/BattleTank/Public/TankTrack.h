// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void ApplySidewayForce();
	void DriveTrack();
	float cummulativeThrottle = 0;

	virtual void BeginPlay() override;
	float currentThrottle = 0;

	UFUNCTION(BlueprintCallable, Category = "Play")
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float throttle);
	
	// This is max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Input")
		float TrackMaxDrivingForce = 400000;	// Assume 40 tonne tank and 1g acceleration
};
