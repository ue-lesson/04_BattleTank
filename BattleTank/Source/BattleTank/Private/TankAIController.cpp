// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	{
		auto PlayerTank = GetPlayerTank();
		auto AIControlledTank = GetControlledTank();
		if (!PlayerTank)
		{	UE_LOG(LogTemp, Warning, TEXT("AI Controller did not found player's tank"), *(PlayerTank->GetName()));   }
		else
		{	UE_LOG(LogTemp, Warning, TEXT("%s found player's: %s"), *(AIControlledTank->GetName()), *(PlayerTank->GetName()));   }
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);

}
