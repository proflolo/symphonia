// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelConfig.generated.h"

class ACameraActor;
class UExplorationMenuEp;

UCLASS()
class SYMPHONIA_API ALevelConfig : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelConfig();

	UPROPERTY(EditAnywhere, DisplayName = "Main Camera")
	ACameraActor* mainCamera;

	UPROPERTY(EditAnywhere, DisplayName = "Ingame Menu")
	TSubclassOf<UExplorationMenuEp> ingameMenuClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
