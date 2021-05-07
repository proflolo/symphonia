// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/MainCharacterEP.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Private/AssertUtils.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"

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
}

// Called every frame
void AMainCharacterEP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_physics)
	{
		m_physics->SetPhysicsLinearVelocity(m_velocity);
		if (m_velocity.SizeSquared() > 0.0f)
		{
			m_lookAt = m_velocity.GetUnsafeNormal();
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

