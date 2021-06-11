// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Components/Interactible.h"

// Sets default values for this component's properties
UInteractible::UInteractible()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UInteractible::NotifyInteracted()
{
	sig_onInteracted.Broadcast();
}

// Called when the game starts
void UInteractible::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractible::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
