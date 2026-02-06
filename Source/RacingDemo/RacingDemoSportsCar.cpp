// Copyright Epic Games, Inc. All Rights Reserved.


#include "RacingDemoSportsCar.h"
#include "RacingDemoSportsWheelFront.h"
#include "RacingDemoSportsWheelRear.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"

ARacingDemoSportsCar::ARacingDemoSportsCar()
{
	// Note: for faster iteration times, the vehicle setup can be tweaked in the Blueprint instead

	// Set up the chassis
	GetChaosVehicleMovement()->ChassisHeight = 144.0f;
	GetChaosVehicleMovement()->DragCoefficient = 0.31f;

	// Set up the wheels
	GetChaosVehicleMovement()->bLegacyWheelFrictionPosition = true;
	GetChaosVehicleMovement()->WheelSetups.SetNum(4);

	GetChaosVehicleMovement()->WheelSetups[0].WheelClass = URacingDemoSportsWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[0].BoneName = FName("Phys_Wheel_FL");
	GetChaosVehicleMovement()->WheelSetups[0].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[1].WheelClass = URacingDemoSportsWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[1].BoneName = FName("Phys_Wheel_FR");
	GetChaosVehicleMovement()->WheelSetups[1].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[2].WheelClass = URacingDemoSportsWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[2].BoneName = FName("Phys_Wheel_BL");
	GetChaosVehicleMovement()->WheelSetups[2].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[3].WheelClass = URacingDemoSportsWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[3].BoneName = FName("Phys_Wheel_BR");
	GetChaosVehicleMovement()->WheelSetups[3].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	// Set up the engine
	// NOTE: Check the Blueprint asset for the Torque Curve
	GetChaosVehicleMovement()->EngineSetup.MaxTorque = 750.0f;
	GetChaosVehicleMovement()->EngineSetup.MaxRPM = 7000.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineIdleRPM = 900.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineBrakeEffect = 0.2f;
	GetChaosVehicleMovement()->EngineSetup.EngineRevUpMOI = 5.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineRevDownRate = 600.0f;

	// Set up the transmission
	GetChaosVehicleMovement()->TransmissionSetup.bUseAutomaticGears = true;
	GetChaosVehicleMovement()->TransmissionSetup.bUseAutoReverse = true;
	GetChaosVehicleMovement()->TransmissionSetup.FinalRatio = 2.81f;
	GetChaosVehicleMovement()->TransmissionSetup.ChangeUpRPM = 6000.0f;
	GetChaosVehicleMovement()->TransmissionSetup.ChangeDownRPM = 2000.0f;
	GetChaosVehicleMovement()->TransmissionSetup.GearChangeTime = 0.2f;
	GetChaosVehicleMovement()->TransmissionSetup.TransmissionEfficiency = 0.9f;

	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios.SetNum(5);
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[0] = 4.25f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[1] = 2.52f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[2] = 1.66f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[3] = 1.22f;
	GetChaosVehicleMovement()->TransmissionSetup.ForwardGearRatios[4] = 1.0f;

	GetChaosVehicleMovement()->TransmissionSetup.ReverseGearRatios.SetNum(1);
	GetChaosVehicleMovement()->TransmissionSetup.ReverseGearRatios[0] = 4.04f;

	// Set up the steering
	// NOTE: Check the Blueprint asset for the Steering Curve
	GetChaosVehicleMovement()->SteeringSetup.SteeringType = ESteeringType::Ackermann;
	GetChaosVehicleMovement()->SteeringSetup.AngleRatio = 0.7f;
}

void ARacingDemoSportsCar::BeginPlay()
{
	Super::BeginPlay();

	Health = 100.f;
	CarDestroyed = false;

	// Gets the car's primitive component for collisions
	CarPrim = Cast<UPrimitiveComponent>(GetRootComponent());

	if (CarPrim)
	{
		// Sets it to trigger car impact on collisions
		CarPrim->SetNotifyRigidBodyCollision(true);
		CarPrim->BodyInstance.bNotifyRigidBodyCollision = true;
		CarPrim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CarPrim->OnComponentHit.AddDynamic(this, &ARacingDemoSportsCar::OnCarImpact);
	}

	// ---my code---
	// Starts the engine audio
	if (UAudioManager* AudioManager = GetWorld()->GetGameInstance()->GetSubsystem<UAudioManager>())
	{
		AudioManager->StartEngine(this);
	}
}


/*
---my code---
*/
void ARacingDemoSportsCar::Tick(float Delta)
{
	Super::Tick(Delta);

	if (UAudioManager* AudioManager = GetWorld()->GetGameInstance()->GetSubsystem<UAudioManager>())
	{
		AudioManager->UpdateHealth(this, Health);

		const FWheelStatus& TireStatus = GetChaosVehicleMovement()->GetWheelState(3);
		if (TireStatus.bIsValid)
		{
			// Gets the cars speed
			if (float CarSpeed = GetChaosVehicleMovement()->GetForwardSpeedMPH())
			{
				// Makes it a positive number
				CarSpeed = FMath::Abs(CarSpeed);
				AudioManager->UpdateSpeed(this, CarSpeed);

				// Updates the tire sounds if the car isn't moving
				if (CarSpeed == 0)
				{
					AudioManager->UpdateTires(this, 3);
				}
				// Updates the tire sounds if the car is skidding
				else if (TireStatus.bIsSkidding)
				{
					AudioManager->UpdateTires(this, 2);
				}
				else
				{
					AudioManager->UpdateTires(this, 1);
				}
			}
			// Updates the surface for if the car is in the air
			if (!TireStatus.bInContact)
			{
				CarWasInAir = true;
				AudioManager->UpdateSurface(this, 3);
			}
			else
			{
				if (CarWasInAir)
				{
					CarWasInAir = false;
					AudioManager->PlayLanding(this);
				}
				FString Surface = TireStatus.PhysMaterial->GetName();
				if (Surface == "Slippery")
				{
					AudioManager->UpdateSurface(this, 2);
				}
				else
				{
					AudioManager->UpdateSurface(this, 1);
				}
			}
		}

		
		if (float Throttle = GetChaosVehicleMovement()->GetThrottleInput())
		{
			AudioManager->UpdateStrain(this, Throttle);
		}
		if (int Gear = GetChaosVehicleMovement()->GetCurrentGear())
		{
			AudioManager->UpdateGear(this, Gear);
		}
	}
}

void ARacingDemoSportsCar::OnCarImpact(UPrimitiveComponent* SportsCar, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector Impulse, const FHitResult& Hit)
{
	if (CarDestroyed)
		return;

	// Calculates the impact
	const float ImpactForce = Impulse.Size();

	// Ignores small bumps
	if (ImpactForce < MinImpact)
		return;

	// Scales impact force to health
	const float Damage = FMath::Clamp(FMath::Max(0.f, (ImpactForce - MinImpact) * ImpactScale), 1.f, 100.f);
	DamageCar(Damage);

	// Handles impact sounds
	if (UAudioManager* AudioManager = GetWorld()->GetGameInstance()->GetSubsystem<UAudioManager>())
	{
		// Sets the impacted surface
		if (OtherActor->ActorHasTag("Solid"))
			AudioManager->SetImpactSurface(this, true);
		else
			AudioManager->SetImpactSurface(this, false);

		// Plays the impact sound according to damage
		AudioManager->SetImpact(this, Damage);
		AudioManager->PlayImpact(this);
	}
}

void ARacingDemoSportsCar::DamageCar(float Damage)
{
	if (Damage <= 0.f || CarDestroyed)
		return;

	// Updates health within range of 0-100 in accordance to damage
	Health = FMath::Clamp(Health - Damage, 0.f, 100.f);

	if (Health <= 0.f)
	{
		DestroyCar();
	}
}

void ARacingDemoSportsCar::DestroyCar()
{
	if (CarDestroyed)
		return;

	CarDestroyed = true;

	// Stops playing the engine sound
	if (UAudioManager* AudioManager = GetWorld()->GetGameInstance()->GetSubsystem<UAudioManager>())
	{
		AudioManager->StopEngine(this);
	}

	Destroy();
}

float ARacingDemoSportsCar::DamageScalar()
{
	// Sets scalar to a value between 0.2 and 1 depending on health
	float Scalar = FMath::Clamp(Health / 100.f, 0.2f, 1.f);

	return Scalar;
}
