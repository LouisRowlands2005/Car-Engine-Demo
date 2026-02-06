// Fill out your copyright notice in the Description page of Project Settings.
/*
---All my code---
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TunnelTrigger.generated.h"

class UBoxComponent;

UCLASS()
class RACINGDEMO_API ATunnelTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATunnelTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBody, bool Sweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBody);

	UPROPERTY(EditAnywhere, Category = "Tunnel")
	UBoxComponent* TunnelBox;
};
