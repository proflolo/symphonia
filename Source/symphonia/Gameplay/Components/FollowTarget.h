// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FollowTarget.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SYMPHONIA_API UFollowTarget : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFollowTarget();

	UPROPERTY(EditAnywhere, DisplayName = "Target")
	AActor* m_target;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector m_delta;
	FVector m_targetSmoothPosition;
};
