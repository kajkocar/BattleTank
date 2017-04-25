// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::ApplySidewayForce()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	// fix side ways slippage of tank while moving
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// work out the required acceleration this frame to correct it
	auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();

	// calculate abd apply sideways force (F = m * a)
	// we have two tracks
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2;  // two tracks
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::BeginPlay()
{
	//Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
// 	UE_LOG(LogTemp, Warning, TEXT("hit"));
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	DriveTrack();
	ApplySidewayForce();
	cummulativeThrottle = 0;
}

void UTankTrack::SetThrottle(float throttle)
{
	cummulativeThrottle = FMath::Clamp<float>( cummulativeThrottle + throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
// 		auto Time = GetWorld()->GetTimeSeconds();
//  	auto Name = GetName();
//  	UE_LOG(LogTemp, Warning, TEXT("%s: SetThrottle %f"), *Name, cummulativeThrottle);

	auto forceApplied = GetForwardVector() * cummulativeThrottle * TrackMaxDrivingForce;
	auto forceLocation = GetComponentLocation();
	
	// owner of track is tank body, just what we need
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}


