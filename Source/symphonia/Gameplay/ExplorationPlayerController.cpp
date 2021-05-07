// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/ExplorationPlayerController.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine/Classes/Camera/CameraActor.h"
#include "Actors/LevelConfig.h"
#include "GameFramework/GameUserSettings.h"
#include "Gui/ExplorationMenuEp.h"
#include "Engine/Classes/Components/SceneCaptureComponent2D.h"
#include "Engine/Classes/Kismet/KismetRenderingLibrary.h"
#include "Private/AssertUtils.h"
#include "Gameplay/Actors/MainCharacterEP.h"


	void AExplorationPlayerController::BeginPlay()
	{
		APlayerController::BeginPlay();

		bShowMouseCursor = true;

		UGameUserSettings* userSettings = GEngine->GetGameUserSettings();
		userSettings->SetFullscreenMode(EWindowMode::Windowed);
		userSettings->SetScreenResolution(FIntPoint(960, 540));
		userSettings->ApplySettings(false);


		const ALevelConfig* levelConfig = dynamic_cast<const ALevelConfig*>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelConfig::StaticClass()));

		ACameraActor* selectedCamera = levelConfig->mainCamera;

		LASSERT(selectedCamera, "No se ha configurado la camara del nivel");
		if (!selectedCamera)
		{
			return;
		}

		USceneCaptureComponent2D* captureComponent = dynamic_cast<USceneCaptureComponent2D*>(selectedCamera->GetComponentByClass(USceneCaptureComponent2D::StaticClass()));
		if (!captureComponent)
		{
			UE_LOG(LogTemp, Error, TEXT("CaptureComponent no encontrada en la camara"));
		}
		FVector2D viewPortSize;
		GEngine->GameViewport->GetViewportSize(viewPortSize);
		if (viewPortSize.Y < 10 || viewPortSize.Y < 10)
		{
			//UE_LOG(LogTemp, Warning!, TEXT("Viewport no encontrado!"));
			viewPortSize = userSettings->GetScreenResolution();
			UE_LOG(LogTemp, Warning, TEXT("Viewport no encontrado"));
		}


		UTextureRenderTarget2D* renderTarget = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), viewPortSize.X, viewPortSize.Y);

		captureComponent->TextureTarget = renderTarget;

		SetViewTarget(selectedCamera);

		m_menu = CreateWidget<UExplorationMenuEp>(GetWorld(), levelConfig->ingameMenuClass);
		m_menu->AddToViewport();
		m_menu->Prepare(renderTarget);
		m_menu->sig_onPauseChangeRequested.AddDynamic(this, &AExplorationPlayerController::PauseChangeRequested);		

		if (levelConfig->mainCharacter)
		{
			Possess(levelConfig->mainCharacter);
		}

	}

	void AExplorationPlayerController::PauseChangeRequested()
	{
		if (IsPaused())
		{
			SetPause(false);
			m_menu->SetPaused(false);
		}
		else
		{
			SetPause(true);
			m_menu->SetPaused(true);
		}
	}
