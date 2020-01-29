// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (GameOverViewActors)
		{
			//make array to take control from player pawn and give to pc
			TArray<AActor*> ReturnActors;
			UGameplayStatics::GetAllActorsOfClass(this, GameOverViewActors, ReturnActors);

			AActor* GameOverSpectators = nullptr;
			//.Num() finds number of objects in the array changes view target if valid actor is found else do nothing
			if (ReturnActors.Num() > 0)
			{
				GameOverSpectators = ReturnActors[0];
				//do we have a player controller 	
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController()); //setting up player controller to receive following task
				if (PC)
				{
					PC->SetViewTargetWithBlend(GameOverSpectators, .5f, EViewTargetBlendFunction::VTBlend_Cubic);
					// view player controller confirmed set to location
					//move to location
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GameOverViewActorsClass is nullptr please ipdate gamemode to change game over view"));
		}
	}

	OnCompleteMission(InstigatorPawn);
}
