// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ExplorationGameMode.h"
#include "ExplorationPlayerController.h"
#include "ExplorationPlayerState.h"


AExplorationGameMode::AExplorationGameMode()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AExplorationPlayerController::StaticClass();
	PlayerStateClass = AExplorationPlayerState::StaticClass();
}