// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacterEP.generated.h"

class UPrimitiveComponent;

UCLASS()
class SYMPHONIA_API AMainCharacterEP : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainCharacterEP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveX(float i_value);
	void MoveY(float i_value);
	void OnAction();

	UPrimitiveComponent* m_physics;
	FVector2D m_rawAxis;
	FVector m_velocity;
	FVector m_lookAt;
	bool m_onActionRequested = false;
};
