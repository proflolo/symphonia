// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestroyAfterTime.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SYMPHONIA_API UDestroyAfterTime : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDestroyAfterTime();

	UPROPERTY(EditAnywhere, DisplayName= "Delay to destroy (s)")
	float m_delayBeforeDestructionSeconds;

	UFUNCTION(BlueprintCallable, Category= "DestroyAfterTime", DisplayName = "Trigger Destruction")
	void TriggerDestruction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	bool m_destructionRequested = false;
	float m_ellapsedTime = 0.f;
		
};
