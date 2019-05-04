// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetCollisionObjectType(ECC_PhysicsBody);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Mesh->SetSimulatePhysics(true);
	SetRootComponent(Cast<USceneComponent>(Mesh));

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &AItem::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping"));
	if (OtherActor != this)
	{
		Caller = OtherActor;
		UE_LOG(LogTemp, Warning, TEXT("NOM"));
	}
}

void AItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Caller = nullptr;
}

void AItem::Equipped()
{
	if (Caller)
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("Equipped"));
	}
}