// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include <Perception/PawnSensingComponent.h>
#include <DrawDebugHelpers.h>
#include <Matrix.h>
#include <RotationMatrix.h>
#include <GameFramework/Actor.h>
#include <TimerManager.h>

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawningSensingComp"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
	//passed in the reset rotation function
	OriginalRotation = GetActorRotation();
}


void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}
	//Helpful for testing before endgame function implemented
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.f, 12, FColor::Red, false, 10.f);
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.f, 12, FColor::Green, false, 10.f);

	//MAkeFromX used a vector Direction handles that unit
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();

	//locking the Pitch and Roll to prevent weird angling of pawn rotation strictly on the yaw
	NewLookAt.Pitch = 0.f;
	NewLookAt.Roll = 0.f;

	SetActorRotation(NewLookAt);

	//clears timer after 3 secs to avoid multiple countdown during hearing noise for example multiple shots
	GetWorldTimerManager().ClearTimer(TimerHandler_ResetRotation);
	GetWorldTimerManager().SetTimer(TimerHandler_ResetRotation, this, &AFPSAIGuard::ResetRotation, 3.0f);

}
void AFPSAIGuard:: ResetRotation()
{
	SetActorRotation(OriginalRotation);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


