// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ExplorationPlayerController.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Camera/CameraActor.h"
#include "Actors/LevelConfig.h"
#include "GameFramework/GameUserSettings.h"
#include "Gui/ExplorationMenuEp.h"



	void AExplorationPlayerController::BeginPlay()
	{
		APlayerController::BeginPlay();


		UGameUserSettings* userSettings = GEngine->GetGameUserSettings();
		userSettings->SetFullscreenMode(EWindowMode::Windowed);
		userSettings->SetScreenResolution(FIntPoint(960, 540));
		userSettings->ApplySettings(false);


		const ALevelConfig* levelConfig = dynamic_cast<const ALevelConfig*>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelConfig::StaticClass()));

		ACameraActor* selectedCamera = levelConfig->mainCamera;

		SetViewTarget(selectedCamera);

		m_menu = CreateWidget<UExplorationMenuEp>(GetWorld(), levelConfig->ingameMenuClass);
		m_menu->AddToViewport();

	}


