// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	{
		auto AIControlledTank = GetControlledTank();
		if (!AIControlledTank)
		{	UE_LOG(LogTemp, Warning, TEXT("%s did not possessed by AI"), *(AIControlledTank->GetName()));   }
		else
		{	UE_LOG(LogTemp, Warning, TEXT("%s  possessed by AI"), *(AIControlledTank->GetName()));   }
	}
}

ATank* ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}