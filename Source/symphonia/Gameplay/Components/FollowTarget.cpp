// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Components/FollowTarget.h"
#include "Private/AssertUtils.h"

// Sets default values for this component's properties
UFollowTarget::UFollowTarget()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFollowTarget::BeginPlay()
{
	Super::BeginPlay();

	LASSERT(m_target, "No tenemos target para la components UFollowTarget");

	if (m_target)
	{
		m_delta = GetOwner()->GetActorLocation() - m_target->GetActorLocation();
		m_targetSmoothPosition = m_target->GetActorLocation();
	}
	
}


// Called every frame
void UFollowTarget::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_target)
	{
		//GetOwner()->SetActorLocation(m_target->GetActorLocation() + m_delta);
		FVector rawPosition = m_target->GetActorLocation() + m_delta;
		float ratio = DeltaTime;
		if (ratio < 1.0f)
		{
			ratio = 0.98f;
		}
		m_targetSmoothPosition = m_targetSmoothPosition * (1- ratio) + rawPosition * ratio;
		GetOwner()->SetActorLocation(m_targetSmoothPosition);
	}
}

