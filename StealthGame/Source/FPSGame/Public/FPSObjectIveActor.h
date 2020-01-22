// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include "FPSObjectIveActor.generated.h"

UCLASS()
class FPSGAME_API AFPSObjectIveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectIveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UParticleSystem* PickUpFX;

	void PlayEffects();

public:	
	/**borrowed from actor class, override function in this case */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
