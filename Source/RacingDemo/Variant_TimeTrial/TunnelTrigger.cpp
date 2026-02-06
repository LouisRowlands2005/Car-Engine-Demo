// Fill out your copyright notice in the Description page of Project Settings.
/*
---All my code---
*/


#include "Variant_TimeTrial/TunnelTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AudioManager.h"

// Sets default values
ATunnelTrigger::ATunnelTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	// Adds tunnel box to the actor to be used for collisions
	TunnelBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TunnelBox);

	// Sets up collisions
	TunnelBox->SetHiddenInGame(true);
	TunnelBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TunnelBox->SetCollisionObjectType(ECC_WorldDynamic);
	TunnelBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TunnelBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TunnelBox->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	TunnelBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATunnelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	TunnelBox->OnComponentBeginOverlap.AddDynamic(this, &ATunnelTrigger::BeginOverlap);
	TunnelBox->OnComponentEndOverlap.AddDynamic(this, &ATunnelTrigger::EndOverlap);
}

void ATunnelTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBody, bool Sweep, const FHitResult& SweepResult)
{
	// If the player enters the tunnel
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		// Update audio to reflect this
		if (UAudioManager* AudioManager = GetWorld()->GetGameInstance()->GetSubsystem<UAudioManager>())
		{
			AudioManager->UpdateTunnel(true);
		}
	}
}

void ATunnelTrigger::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBody)
{
	// If the player leaves the tunnel
	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		// Update audio to reflect this
		if (UAudioManager* AudioManager = GetWorld()->GetGameInstance()->GetSubsystem<UAudioManager>())
		{
			AudioManager->UpdateTunnel(false);
		}
	}
}
