// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	currentHealth = StartingHealth;
	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UHealthComponent::IsOwnerAlive() const
{
	return currentHealth > MinimumHealth;
}

float UHealthComponent::GetCurrentHealth() const
{
	return currentHealth;
}

void UHealthComponent::TakeDamage(float Damage)
{
	currentHealth -= Damage;
	
	if (!IsOwnerAlive())
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::RegenerateHealth(float RegeneratedValue)
{
	currentHealth = FMath::Clamp<float>(currentHealth + RegeneratedValue, MinimumHealth, MaximumHealth);
}