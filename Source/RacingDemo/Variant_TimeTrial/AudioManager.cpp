// Fill out your copyright notice in the Description page of Project Settings.

// ---audio manager is all my code---

#include "Variant_TimeTrial/AudioManager.h"
#include "Wwise/API/WwiseSoundEngineAPI.h"

UAudioManager::UAudioManager()
{
	// Sets events to match their variables
	static ConstructorHelpers::FObjectFinder<UAkAudioEvent> StartEvent(TEXT("/Script/AkAudio.AkAudioEvent'/Game/WwiseAudio/Events/Default_Work_Unit/StartEngine.StartEngine'"));
	StartEngineEvent = StartEvent.Object;

	static ConstructorHelpers::FObjectFinder<UAkAudioEvent> StopEvent(TEXT("/Script/AkAudio.AkAudioEvent'/Game/WwiseAudio/Events/Default_Work_Unit/StopEngine.StopEngine'"));
	StopEngineEvent = StopEvent.Object;

	static ConstructorHelpers::FObjectFinder<UAkAudioEvent> ImpactEvent(TEXT("/Script/AkAudio.AkAudioEvent'/Game/WwiseAudio/Events/Default_Work_Unit/PlayImpact.PlayImpact'"));
	PlayImpactEvent = ImpactEvent.Object;
	
	static ConstructorHelpers::FObjectFinder<UAkAudioEvent> LandingEvent(TEXT("/Script/AkAudio.AkAudioEvent'/Game/WwiseAudio/Events/Default_Work_Unit/PlayLanding.PlayLanding'"));
	PlayLandingEvent = LandingEvent.Object;
}

void UAudioManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAudioManager::Deinitialize()
{
	Super::Deinitialize();
}

void UAudioManager::StartEngine(AActor* Car)
{
	// Gets the sound engine
	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		if (StartEngineEvent && Car)
		{
			// Checks if there is a component for sound on the car
			TArray<UAkComponent*> Components;
			Car->GetComponents(Components);

			// If there are no components for sound
			if (Components.Num() == 0)
			{
				// Loads the sound event if it's not already loaded
				if (!StartEngineEvent->IsLoaded())
				{
					StartEngineEvent->LoadData();
				}

				// Adds the component for the sound to the car
				auto* AkAudioComponent = NewObject<UAkComponent>(Car);
				AkAudioComponent->SetupAttachment(Car->GetDefaultAttachComponent());
				Components.Add(AkAudioComponent);
				AkAudioComponent->RegisterComponent();
			}
			// Plays the sound
			SoundEngine->PostEvent(StartEngineEvent->GetWwiseShortID(), Components[0]->GetAkGameObjectID());
		}
	}
}

void UAudioManager::StopEngine(AActor* Car)
{
	// Gets the sound engine
	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		if (StartEngineEvent && Car)
		{
			// Checks if there is a component for sound on the car
			TArray<UAkComponent*> Components;
			Car->GetComponents(Components);

			// If there are no components for sound
			if (Components.Num() == 0)
			{
				// Loads the sound event if it's not already loaded
				if (!StartEngineEvent->IsLoaded())
				{
					StartEngineEvent->LoadData();
				}

				// Adds the component for the sound to the car
				auto* AkAudioComponent = NewObject<UAkComponent>(Car);
				AkAudioComponent->SetupAttachment(Car->GetDefaultAttachComponent());
				Components.Add(AkAudioComponent);
				AkAudioComponent->RegisterComponent();
			}
			// Stops playing the sound
			SoundEngine->PostEvent(StopEngineEvent->GetWwiseShortID(), Components[0]->GetAkGameObjectID());
		}
	}
}

void UAudioManager::PlayImpact(AActor* Car)
{
	// Gets the sound engine
	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		if (PlayImpactEvent && Car)
		{
			// Checks if there is a component for sound on the car
			TArray<UAkComponent*> Components;
			Car->GetComponents(Components);

			// If there are no components for sound
			if (Components.Num() == 0)
			{
				// Loads the sound event if it's not already loaded
				if (!PlayImpactEvent->IsLoaded())
				{
					PlayImpactEvent->LoadData();
				}

				// Adds the component for the sound to the car
				auto* AkAudioComponent = NewObject<UAkComponent>(Car);
				AkAudioComponent->SetupAttachment(Car->GetDefaultAttachComponent());
				Components.Add(AkAudioComponent);
				AkAudioComponent->RegisterComponent();
			}
			// Plays the sound
			SoundEngine->PostEvent(PlayImpactEvent->GetWwiseShortID(), Components[0]->GetAkGameObjectID());
		}
	}
}

void UAudioManager::PlayLanding(AActor* Car)
{
	// Gets the sound engine
	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		if (PlayLandingEvent && Car)
		{
			// Checks if there is a component for sound on the car
			TArray<UAkComponent*> Components;
			Car->GetComponents(Components);

			// If there are no components for sound
			if (Components.Num() == 0)
			{
				// Loads the sound event if it's not already loaded
				if (!PlayLandingEvent->IsLoaded())
				{
					PlayLandingEvent->LoadData();
				}

				// Adds the component for the sound to the car
				auto* AkAudioComponent = NewObject<UAkComponent>(Car);
				AkAudioComponent->SetupAttachment(Car->GetDefaultAttachComponent());
				Components.Add(AkAudioComponent);
				AkAudioComponent->RegisterComponent();
			}
			// Plays the sound
			SoundEngine->PostEvent(PlayLandingEvent->GetWwiseShortID(), Components[0]->GetAkGameObjectID());
		}
	}
}

void UAudioManager::UpdateSpeed(AActor* Car, float Speed)
{
	// Scales speed to fit into the 0-100 scale
	Speed = FMath::Clamp(Speed / 1.5, 0, 100);

	// Gets audio component of car
	TArray<UAkComponent*> Components;
	Car->GetComponents(Components);
	if (Components.Num() == 0)
		return;

	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		// Gets ID for the speed variable
		const AkRtpcID SpeedRTPC = SoundEngine->GetIDFromString("Speed");

		// Updates speed
		SoundEngine->SetRTPCValue(SpeedRTPC, Speed, Components[0]->GetAkGameObjectID());
	}
}

void UAudioManager::UpdateHealth(AActor* Car, float Health)
{
	Health = FMath::Clamp(Health, 0, 100);

	// Gets audio component of car
	TArray<UAkComponent*> Components;
	Car->GetComponents(Components);
	if (Components.Num() == 0)
		return;

	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		// Gets ID for the health variable
		const AkRtpcID HealthRTPC = SoundEngine->GetIDFromString("Health");

		// Updates health
		SoundEngine->SetRTPCValue(HealthRTPC, Health, Components[0]->GetAkGameObjectID());
	}
}

void UAudioManager::UpdateStrain(AActor* Car, float Strain)
{
	// Scales strain to fit the 0-100 scale
	Strain = FMath::Clamp(Strain * 100, 0, 100);

	// Gets audio component of car
	TArray<UAkComponent*> Components;
	Car->GetComponents(Components);
	if (Components.Num() == 0)
		return;

	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		// Gets ID for the strain variable
		const AkRtpcID StrainRTPC = SoundEngine->GetIDFromString("Strain");

		// Updates strain
		SoundEngine->SetRTPCValue(StrainRTPC, Strain, Components[0]->GetAkGameObjectID());
	}
}

void UAudioManager::SetImpact(AActor* Car, float Impact)
{
	Impact = FMath::Clamp(Impact, 0, 100);

	// Gets audio component of car
	TArray<UAkComponent*> Components;
	Car->GetComponents(Components);
	if (Components.Num() == 0)
		return;

	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		// Gets ID for the impact variable
		const AkRtpcID ImpactRTPC = SoundEngine->GetIDFromString("Impact");

		// Updates impact
		SoundEngine->SetRTPCValue(ImpactRTPC, Impact, Components[0]->GetAkGameObjectID());
	}
}

void UAudioManager::UpdateGear(AActor* Car, int Gear)
{
	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		// Gets audio component of car
		TArray<UAkComponent*> Components;
		Car->GetComponents(Components);
		if (Components.Num() == 0)
			return;

		// Gets ID for the gear switch
		const AkSwitchGroupID GearSwitch = SoundEngine->GetIDFromString("Gear");

		// Gets corresponding gear name to current gear
		const char* GearName = nullptr;
		switch (Gear)
		{
		case -1:
			GearName = "Reverse";
			break;
		case 0:
			GearName = "Neutral";
			break;

		case 1:
			GearName = "One";
			break;

		case 2:
			GearName = "Two";
			break;

		case 3:
			GearName = "Three";
			break;

		case 4:
			GearName = "Four";
			break;

		case 5:
			GearName = "Five";
			break;
		default:
			return;
		}

		// Gets ID for current gear
		const AkSwitchStateID CurrentGear = SoundEngine->GetIDFromString(GearName);

		// Updates the switch
		SoundEngine->SetSwitch(GearSwitch, CurrentGear, Components[0]->GetAkGameObjectID());
	}
}

void UAudioManager::UpdateSurface(AActor* Car, int Surface)
{
	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		// Gets audio component of car
		TArray<UAkComponent*> Components;
		Car->GetComponents(Components);
		if (Components.Num() == 0)
			return;

		// Gets ID for the surface switch
		const AkSwitchGroupID SurfaceSwitch = SoundEngine->GetIDFromString("Surface");

		// Gets corresponding surface name to current surface
		const char* SurfaceName = nullptr;
		switch (Surface)
		{
		case 1:
			SurfaceName = "Ground";
			break;

		case 2:
			SurfaceName = "Sand";
			break;

		case 3:
			SurfaceName = "Air";
			break;

		default:
			return;
		}

		// Gets ID for current surface
		const AkSwitchStateID CurrentSurface = SoundEngine->GetIDFromString(SurfaceName);

		// Updates the switch
		SoundEngine->SetSwitch(SurfaceSwitch, CurrentSurface, Components[0]->GetAkGameObjectID());
	}
}

void UAudioManager::UpdateTires(AActor* Car, int Status)
{
	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		// Gets audio component of car
		TArray<UAkComponent*> Components;
		Car->GetComponents(Components);
		if (Components.Num() == 0)
			return;

		// Gets ID for the tire switch
		const AkSwitchGroupID TireStatus = SoundEngine->GetIDFromString("TireStatus");

		// Gets corresponding tire status name to current tire status
		const char* StatusName = nullptr;
		switch (Status)
		{
		case 1:
			StatusName = "Rolling";
			break;

		case 2:
			StatusName = "Skidding";
			break;

		case 3:
			StatusName = "Stopped";
			break;

		default:
			return;
		}

		// Gets ID for current tire status
		const AkSwitchStateID CurrentStatus = SoundEngine->GetIDFromString(StatusName);

		// Updates the switch
		SoundEngine->SetSwitch(TireStatus, CurrentStatus, Components[0]->GetAkGameObjectID());
	}
}

void UAudioManager::SetImpactSurface(AActor* Car, bool Solid)
{
	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		// Gets audio component of car
		TArray<UAkComponent*> Components;
		Car->GetComponents(Components);
		if (Components.Num() == 0)
			return;

		// Gets ID for the impact surface switch
		const AkSwitchGroupID ImpactSurface = SoundEngine->GetIDFromString("ImpactSurface");

		// Gets corresponding impact surface name to hit impact surface
		const char* StatusName = nullptr;
		if (Solid)
			StatusName = "Solid";
		else
			StatusName = "Sand";

		// Gets ID for current tire status
		const AkSwitchStateID ImpactedSurface = SoundEngine->GetIDFromString(StatusName);

		// Updates the switch
		SoundEngine->SetSwitch(ImpactSurface, ImpactedSurface, Components[0]->GetAkGameObjectID());
	}
}

void UAudioManager::UpdateTunnel(bool Tunnel)
{
	if (auto* SoundEngine = IWwiseSoundEngineAPI::Get())
	{
		// Gets ID for the tunnel state
		const AkStateGroupID TunnelState = SoundEngine->GetIDFromString("Tunnel");
		const char* TunnelStatus = nullptr;
		if (Tunnel)
		{
			TunnelStatus = "True";
		}
		else
		{
			TunnelStatus = "False";
		}

		// Gets ID for the tunnel status
		const AkStateID TunnelID = SoundEngine->GetIDFromString(TunnelStatus);
		SoundEngine->SetState(TunnelState, TunnelID);
	}
}

