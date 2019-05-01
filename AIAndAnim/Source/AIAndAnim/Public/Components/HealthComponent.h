// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AIANDANIM_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Death")
	FOnDeath OnDeath;

	UFUNCTION(BlueprintCallable)
	bool IsOwnerAlive() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void RegenerateHealth(float RegeneratedValue);

private:
	UPROPERTY(VisibleAnywhere, Category = "Health")
	float currentHealth;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float StartingHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MinimumHealth = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float MaximumHealth = 100.f;
};
