// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controledTank = GetPawn();

	if (!ensure(playerTank && controledTank)) { return; }

	MoveToActor(playerTank, AcceptaceRadius);

	auto aimingComponent = controledTank->FindComponentByClass<UTankAimingComponent>();
	aimingComponent->AimAt(playerTank->GetActorLocation());

	if( aimingComponent->GetFiringState() == EFiringStatus::Locked)
		aimingComponent->Fire();
}


