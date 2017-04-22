// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// How close can the AI tank get to player
	UPROPERTY(BlueprintReadOnly, Category = Setup)
		float AcceptaceRadius = 300.0f;		// 3000

private:
	virtual void BeginPlay() override;
	
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

};
