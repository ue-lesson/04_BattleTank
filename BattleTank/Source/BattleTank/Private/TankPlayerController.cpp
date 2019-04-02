// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankPlayerController.h"
#include "Engine/World.h"
#include "BattleTank.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{ 	UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a Tank"));  }
	else 
	{ UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));  }	
}

void ATankPlayerController::Tick(float deltatime)
{
	Super::Tick(deltatime);
	AimTowardCrosshair();	
	//UE_LOG(LogTemp, Warning, TEXT("Player Controller Ticking"));

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; //OutParameter
	if (GetSightRayHitLocation(OutHitLocation)) //Has "side-effect", is going line trace
	{
		GetControlledTank()->AimAt(OutHitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	// Find the crosshair position in viewport
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ViewportLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the viewport position of the crosshair to the world direction (look direction)
	FVector LookDirection;
	if (GetLookDirection(ViewportLocation, LookDirection))
	{
		///UE_LOG(LogTemp, Warning, TEXT("Look Location: %s"), *LookDirection.ToString());

		// Line-trace the look direction and get what is being hit in the world (up to MAX range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ViewportLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation; //To be discarded
	
	return DeprojectScreenPositionToWorld(
		ViewportLocation.X,
		ViewportLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false; // Line Trace didn't succeed
}