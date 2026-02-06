// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RacingDemo : ModuleRules
{
	public RacingDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"AkAudio",
			"WwiseSoundEngine",
            "InputCore",
			"EnhancedInput",
			"ChaosVehicles",
			"PhysicsCore",
			"UMG",
			"Slate"
		});

		PublicIncludePaths.AddRange(new string[] {
			"RacingDemo",
			"RacingDemo/SportsCar",
			"RacingDemo/OffroadCar",
			"RacingDemo/Variant_Offroad",
			"RacingDemo/Variant_TimeTrial",
			"RacingDemo/Variant_TimeTrial/UI"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
