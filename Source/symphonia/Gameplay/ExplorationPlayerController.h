// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExplorationPlayerController.generated.h"

class UExplorationMenuEp;


	/**
	 *
	 */
	UCLASS()
		class SYMPHONIA_API AExplorationPlayerController : public APlayerController
	{
		GENERATED_BODY()

	public:

		void BeginPlay() override;

	private:
		UExplorationMenuEp* m_menu;

		UFUNCTION()
		void PauseChangeRequested();

	};