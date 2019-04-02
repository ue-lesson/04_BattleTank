// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "BattleTank.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity(0); //// WHY(this is what will we get from this whole function)?
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);
	}
	//If no solution found, do nothing 
}


void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{

	// Work-out between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("Barrel rotate from %s to %s"), *BarrelRotator.ToString(), *AimAsRotator.ToString());

	// Move the barrel the right amount this frame
	// Given a max elevation speed and frame time


	//////FVector DeltaAim = StartLocation - OutHitLocation;
	//////bool bMoveBarrel = USceneComponent::MoveComponent (DeltaAim,Add,true,OutHitLocation,EMoveComponentFlags::MOVECOMP_NoFlags,ETeleportType::None);
}



