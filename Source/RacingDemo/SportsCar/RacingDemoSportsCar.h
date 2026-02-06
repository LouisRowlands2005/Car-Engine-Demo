// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RacingDemoPawn.h"
#include "RacingDemoSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class ARacingDemoSportsCar : public ARacingDemoPawn
{
	GENERATED_BODY()
	
public:

	ARacingDemoSportsCar();

	virtual void BeginPlay() override;
	virtual void Tick(float Delta) override;

	/*
	---my code---
	*/
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const { return Health; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float Health = 100.f;

	// Used so car is only damaged when it hits something properly
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MinImpact = 10000.f;

	// Scales the impact damage to the health
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float ImpactScale = 0.0001f;

	bool CarDestroyed = false;
	bool CarWasInAir = false;

	UFUNCTION()
	void OnCarImpact(UPrimitiveComponent* SportsCar, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector Impulse, const FHitResult& Hit);
	UFUNCTION()
	void DamageCar(float Damage);
	UFUNCTION()
	void DestroyCar();

	// Used for collisions
	UPrimitiveComponent* CarPrim = nullptr;

	// Used to scale speed and acceleration to health
	virtual float DamageScalar() override;
};
