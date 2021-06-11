// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Components/DestroyAfterTime.h"

// Sets default values for this component's properties
UDestroyAfterTime::UDestroyAfterTime()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UDestroyAfterTime::TriggerDestruction()
{
	m_destructionRequested = true;
	m_ellapsedTime = 0.f;
}

// Called when the game starts
void UDestroyAfterTime::BeginPlay()
{
	Super::BeginPlay();

	m_destructionRequested = false;
	
}


// Called every frame
void UDestroyAfterTime::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_destructionRequested)
	{
		m_ellapsedTime += DeltaTime;
		if (m_ellapsedTime >= m_delayBeforeDestructionSeconds)
		{
			GetOwner()->Destroy();
			m_destructionRequested = false;
		}
	}
}

