// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectIveActor.h"
#include <Kismet/GameplayStatics.h>
#include "FPSCharacter.h"
#include <LogMacros.h>

// Sets default values
AFPSObjectIveActor::AFPSObjectIveActor()
{
 	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;
	if (!MeshComp)
	{
		/*UE_LOG(LogTemp, Error, TEXT("%s MeshComp not found"), GetComponents)*/
	}
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp, NAME_None);
	
}

// Called when the game starts or when spawned
void AFPSObjectIveActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayEffects();
}

void AFPSObjectIveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickUpFX, GetActorLocation());
}

// Called every frame


void AFPSObjectIveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->bIsCarryingObjective = true;

		Destroy();
	}
}

