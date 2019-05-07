// Fill out your copyright notice in the Description page of Project Settings.

#include "Animal.h"
#include "HealthComponent.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"

// Sets default values
AAnimal::AAnimal()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnDeath.AddDynamic(this, &AAnimal::OnDeath);
}

// Called every frame
void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAnimal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAnimal::SetHealthComponent(UHealthComponent* NewComponent)
{
	HealthComponent = NewComponent;
}

void AAnimal::OnDeath()
{
	bIsAlive = false;
	HealthComponent->DestroyComponent();
	
	HealthComponent = nullptr;
	ChangeToRagdoll();
}

void AAnimal::ChangeToRagdoll()
{
	UCapsuleComponent* AnimalCapsule = GetCapsuleComponent();
	USkeletalMeshComponent* AnimalMesh = GetMesh();

	if (!AnimalMesh || !AnimalCapsule)
	{
		return;
	}

	FName Root = AnimalMesh->GetBoneName(0);

	AnimalMesh->SetAllBodiesBelowSimulatePhysics(Root, true, true);
	AnimalMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	AnimalMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	AnimalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AnimalMesh->SetSimulatePhysics(true);

	AnimalCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	AnimalCapsule->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	UCharacterMovementComponent* AnimalMovementComponent = GetCharacterMovement();

	if (!AnimalMovementComponent)
	{
		return;
	}

	AnimalMovementComponent->GravityScale = 0.f;
}

bool AAnimal::IsAlive() const
{
	return bIsAlive;
}