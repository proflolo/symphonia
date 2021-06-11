// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/MainCharacterEP.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Private/AssertUtils.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Gameplay/Components/Interactible.h"
// Sets default values
AMainCharacterEP::AMainCharacterEP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharacterEP::BeginPlay()
{
	Super::BeginPlay();
	m_physics = FindComponentByClass<UPrimitiveComponent>();
	LASSERT(m_physics, "No hay componente fisica compatible en el Main Character");

	m_rawAxis.X = 0.f;
	m_rawAxis.Y = 0.f;
	m_velocity.X = 0.f;
	m_velocity.Y = 0.f;
	m_velocity.Z = 0.f;

	m_lookAt.X = 1.0f;
	m_lookAt.Y = 0.f;
	m_lookAt.Z = 0.f;

	m_onActionRequested = false;
}

// Called every frame
void AMainCharacterEP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_physics)
	{
		//m_physics->SetPhysicsLinearVelocity(m_velocity);

		float velocitySize = m_velocity.Size();
		if (velocitySize > 0.f)
		{
			//tirar un ray
			FVector radius = m_physics->Bounds.BoxExtent;
			float r = FGenericPlatformMath::Max(radius.X, radius.Y);
			FVector direction = m_velocity.GetSafeNormal();
			FVector start = GetActorLocation() + FVector(0.f, 0.f, -30.f) + r*1.25f * direction;
			FVector end = start + direction*velocitySize*DeltaTime;

			FCollisionObjectQueryParams query(FCollisionObjectQueryParams::InitType::AllObjects);
			FHitResult hit;
			if (GetWorld()->LineTraceSingleByObjectType(hit, start, end, query))
			{
				FVector finalVelocity = FVector::VectorPlaneProject(m_velocity, hit.Normal);
				m_physics->SetPhysicsLinearVelocity(finalVelocity);
			}
			else
			{
				m_physics->SetPhysicsLinearVelocity(m_velocity);
			}

			//si el rayo toca, no avanzar

			//si no toca, avanzar

		
				m_lookAt = m_velocity.GetUnsafeNormal();
		
		}
		else
		{
			m_physics->SetPhysicsLinearVelocity(FVector::ZeroVector);
		}

		if (m_onActionRequested)
		{
			FVector direction = m_lookAt.GetSafeNormal();
			FVector start = GetActorLocation() - FVector(0.f, 0.f, 25.f);
			FVector end = start + direction * 125.0f;

			FCollisionObjectQueryParams query(FCollisionObjectQueryParams::InitType::AllObjects);
			FHitResult hit;
			if (GetWorld()->LineTraceSingleByObjectType(hit, start, end, query))
			{
				UInteractible* impacted = hit.Actor->FindComponentByClass<UInteractible>();
				if (impacted)
				{
					impacted->NotifyInteracted();
				}
			}
			

			m_onActionRequested = false;
		}
		
		
		
		FRotator rotator = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, m_lookAt);
		m_physics->SetAllPhysicsRotation(rotator);
	
	}

}

// Called to bind functionality to input
void AMainCharacterEP::SetupPlayerInputComponent(UInputComponent* i_playerInputComponent)
{
	Super::SetupPlayerInputComponent(i_playerInputComponent);
	i_playerInputComponent->BindAxis("MoveX", this, &AMainCharacterEP::MoveX);
	i_playerInputComponent->BindAxis("MoveY", this, &AMainCharacterEP::MoveY);
	i_playerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &AMainCharacterEP::OnAction);


}

void AMainCharacterEP::MoveX(float i_value)
{
	m_rawAxis.X = i_value;
	m_velocity.X = -i_value * 500.f;
}

void AMainCharacterEP::MoveY(float i_value)
{
	m_rawAxis.Y = i_value;
	m_velocity.Y = i_value * 500.f;
}

void AMainCharacterEP::OnAction()
{
	m_onActionRequested = true;
}

