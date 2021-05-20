// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/Pawn.h"
#include "ShooterPlayerController.h"
#include "ShooterAIController.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)	
{
	Super::PawnKilled(PawnKilled);
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}
	int AIControllersNumber = 0;
	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// controller instance is on winning team and is player controller?
		// if player won and is player controller => true
		// if player lost and is player controller => false
		// if player won and is not a player controller => false
		// if player lost an is not a palyer controller => true
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		// bIsWinner if controller is on wining team.
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}