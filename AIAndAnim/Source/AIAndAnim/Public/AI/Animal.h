// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animal.generated.h"

UCLASS()
class AIANDANIM_API AAnimal : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAnimal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "Health")
	class UHealthComponent* HealthComponent = nullptr;

	UFUNCTION()
	void OnDeath();

protected:
	UFUNCTION(BlueprintCallable)
	void SetHealthComponent(UHealthComponent* NewComponent);

	UPROPERTY(VisibleDefaultsOnly, Category = "Health")
	bool bIsAlive = true;

private:
	void ChangeToRagdoll();
};
