// Fill out your copyright notice in the Description page of Project Settings.


// ---audio manager is all my code---
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AkAudioEvent.h"
#include "AkComponent.h"
#include "AudioManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RACINGDEMO_API UAudioManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	UAudioManager();

	// Called at the start and end of each game instance
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Functions called in the car class to start the engine sound
	UFUNCTION(BlueprintCallable)
	void StartEngine(AActor* Car);
	UFUNCTION(BlueprintCallable)
	void StopEngine(AActor* Car);
	UFUNCTION(BlueprintCallable)
	void PlayImpact(AActor* Car);
	UFUNCTION(BlueprintCallable)
	void PlayLanding(AActor* Car);

	// Functions used to update RTPC variables
	UFUNCTION(BlueprintCallable)
	void UpdateSpeed(AActor* Car, float Speed);
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(AActor* Car, float Health);
	UFUNCTION(BlueprintCallable)
	void UpdateStrain(AActor* Car, float Strain);
	UFUNCTION(BlueprintCallable)
	void SetImpact(AActor* Car, float Impact);

	// Functions used to update switches and states
	UFUNCTION(BlueprintCallable)
	void UpdateGear(AActor* Car, int Gear);
	UFUNCTION(BlueprintCallable)
	void UpdateSurface(AActor* Car, int Surface);
	UFUNCTION(BlueprintCallable)
	void UpdateTires(AActor* Car, int Status);
	UFUNCTION(BlueprintCallable)
	void SetImpactSurface(AActor* Car, bool Solid);
	UFUNCTION(BlueprintCallable)
	void UpdateTunnel(bool Tunnel);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Wwise")
	UAkAudioEvent* StartEngineEvent;
	UPROPERTY(EditDefaultsOnly, Category = "Wwise")
	UAkAudioEvent* StopEngineEvent;
	UPROPERTY(EditDefaultsOnly, Category = "Wwise")
	UAkAudioEvent* PlayImpactEvent;
	UPROPERTY(EditDefaultsOnly, Category = "Wwise")
	UAkAudioEvent* PlayLandingEvent;
};
