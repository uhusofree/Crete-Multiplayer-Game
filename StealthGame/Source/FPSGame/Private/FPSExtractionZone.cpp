// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include <Components/SceneComponent.h>
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include <GameFramework/Actor.h>
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComponent->SetBoxExtent(FVector(200.f));
	RootComponent = OverlapComponent;

	OverlapComponent->SetHiddenInGame(false);
	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComp->DecalSize = FVector(200.f, 200.f, 200.f);
	DecalComp->SetupAttachment(RootComponent);
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter == nullptr)
	{
		return;
	}

	if (MyCharacter->bIsCarryingObjective)
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveObtainedSound);
		AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->CompleteMission(MyCharacter);
		}
		
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Overlapped to extraction zone"));
}
