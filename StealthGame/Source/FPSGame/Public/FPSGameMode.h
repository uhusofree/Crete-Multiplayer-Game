// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <SubclassOf.h>
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "GameOverView")
	TSubclassOf<AActor> GameOverViewActors;
public:

	AFPSGameMode();
	void CompleteMission(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCompleteMission(APawn* InstigatorPawn);
};



