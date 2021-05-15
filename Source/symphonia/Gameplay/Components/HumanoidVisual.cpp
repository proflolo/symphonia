// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Components/HumanoidVisual.h"
#include "Engine/Classes/Components/SkeletalmeshComponent.h"
#include "Engine/Classes/Animation/AnimInstance.h"
#include "Private/AssertUtils.h"

// Sets default values for this component's properties
UHumanoidVisual::UHumanoidVisual()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHumanoidVisual::BeginPlay()
{
	Super::BeginPlay();

	m_skeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	LASSERT(m_skeletalMesh, "No hemos encontrado skeletal mesh en el actor");
	if (m_skeletalMesh)
	{
		m_animInstance = m_skeletalMesh->GetAnimInstance();
		LASSERT(m_animInstance, "No tenemos Animation Instance");
		if (m_animInstance)
		{
			m_speed = FindFProperty<FFloatProperty>(m_animInstance->GetClass(), "Speed");
		}
	}
	
	m_physics = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	LASSERT(m_physics, "No hay componente fisica compatible en el Main Character");
	
}


// Called every frame
void UHumanoidVisual::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_speed && m_physics)
	{
		FVector velocity = m_physics->GetPhysicsLinearVelocity();
		
		float speed = velocity.Size();
		m_speed->SetPropertyValue_InContainer(m_animInstance, speed/ 500.f);

		
	}
}

