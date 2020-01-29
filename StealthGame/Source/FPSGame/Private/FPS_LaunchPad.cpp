// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_LaunchPad.h"
#include <GameFramework/Actor.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AFPS_LaunchPad::AFPS_LaunchPad()
{
	OverlapComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	OverlapComponent->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = OverlapComponent;

	LaunchMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	LaunchMesh->SetupAttachment(OverlapComponent);

	//Bind to Event
	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPS_LaunchPad::OverlapLaunchPad);

	LaunchStrength = 1500.f;
	LaunchPitchAngle = 35.f;
}

	// Called when the game starts or when spawned
	void AFPS_LaunchPad::BeginPlay()
	{
		Super::BeginPlay();

	}

	void AFPS_LaunchPad::OverlapLaunchPad(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
	{
		//Make actor Rotator with our specified pitch and convert to a dirrection vector multiplied by instensity
		FRotator LaunchDirection = GetActorRotation();
		LaunchDirection.Pitch += LaunchPitchAngle;
		//Make launch velocity by turning rotator to a vector multiplying with a our specified strength
		FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

		//Cast to actor in the method parameter
		ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
		//run check if we have casted acharacter 
		if (OtherCharacter)
		{
			//Launch Player is a method from Acharacter class booleans give consistent launch velocity while ignore the player current velocity;
			OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchParticles, GetActorLocation());
			UGameplayStatics::PlaySound2D(GetWorld(), LaunchSound, 1.f);
		}
		//did not overlap a player , check OtherComp if it has physics simulating then launch
		if (OtherComp && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchParticles, GetActorLocation());
			UGameplayStatics::PlaySound2D(GetWorld(), LaunchSound, 1.f);
		}
	}



