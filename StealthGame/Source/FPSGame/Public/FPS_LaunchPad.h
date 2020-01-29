// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include <Components/DecalComponent.h>
#include <Sound/SoundBase.h>
#include <Particles/ParticleSystem.h>
#include "FPS_LaunchPad.generated.h"

UCLASS()
class FPSGAME_API AFPS_LaunchPad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPS_LaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Pad Details")
		UBoxComponent* OverlapComponent;
	//need a static mesh for pad visualization
	UPROPERTY(VisibleAnywhere, Category = "Pad Details")
		UStaticMeshComponent* LaunchMesh;
	//particle effect on launch
	UPROPERTY(EditDefaultsOnly, Category = "Pad Details")
		UParticleSystem* LaunchParticles;
	//sound effect on launch 
	UPROPERTY(EditDefaultsOnly, Category = "Pad Details")
		USoundBase* LaunchSound;
	//decals 
	UPROPERTY(EditDefaultsOnly, Category = "Pad Details")
		UDecalComponent* LaunchDecal;
	//Marked with ufunction to bind to overlap event
	UFUNCTION()
		void OverlapLaunchPad(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/**Total impulse aded to the character on overlap marked editinstanceonly to allow in level editing of this property per instance*/
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchStrength;
	/**Angle added on top of actor rotation to launch the character marked  editinstanceonly to allow in level editing of this property per instance*/
	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
		float LaunchPitchAngle;


};
