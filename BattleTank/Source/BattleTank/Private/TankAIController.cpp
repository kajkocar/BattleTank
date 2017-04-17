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

	auto playerTank = GetPlayerTank();
	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can not find player tank !!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank %s"), *playerTank->GetName());
	}


	UE_LOG(LogTemp, Warning, TEXT("ATankAIController Begin Play"));
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
	AimTowardsPlayer();
	//	UE_LOG(LogTemp, Warning, TEXT("Player controller ticking !!!"));

}

void ATankAIController::AimTowardsPlayer()
{
	auto player = GetPlayerTank();
	if (!player)
		return;

	auto me = GetControlledTank();
	if (!me)
		return;

	me->AimAt(player->GetActorLocation());
}

