// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	HeadsUpDisplay = CreateWidget(this, HUDScreenClass);
	if (HeadsUpDisplay != nullptr)
	{
		HeadsUpDisplay->AddToViewport();
	}
}
void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner); 
	HeadsUpDisplay->RemoveFromViewport();
	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}
	}
	GetWorldTimerManager().SetTimer(RestartTimer, this,&APlayerController::RestartLevel,RestartDelay);
}