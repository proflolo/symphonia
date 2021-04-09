// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Components/CircularMovement.h"

// Sets default values for this component's properties
UCircularMovement::UCircularMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCircularMovement::BeginPlay()
{
	Super::BeginPlay();

	m_ellapsedTimeInSeconds = 0.0f;

	AActor* actor = GetOwner();
	m_initialPosition = actor->GetActorLocation();
	
}


// Called every frame
void UCircularMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	m_ellapsedTimeInSeconds += DeltaTime;
	FVector up(0.f, 0.f, 1.f);
	FVector right(1.f, 0.f, 0.f);
	FVector newPosition = m_initialPosition
		+ FMath::Sin(2.f * PI * m_ellapsedTimeInSeconds / m_circleTimeInSeconds) * m_radiusInMeters * up
		+ FMath::Cos(2.f * PI * m_ellapsedTimeInSeconds / m_circleTimeInSeconds) * m_radiusInMeters * right;
	AActor* owner = GetOwner();
	owner->SetActorLocation(newPosition);
}

