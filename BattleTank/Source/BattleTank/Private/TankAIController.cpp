// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerTank)
		return nullptr;

	return Cast<ATank>(playerTank);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		MoveToActor(GetPlayerTank(), AcceptaceRadius);

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		GetControlledTank()->Fire();
	}
}


