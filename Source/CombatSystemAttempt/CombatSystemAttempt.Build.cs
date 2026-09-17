// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CombatSystemAttempt : ModuleRules
{
	public CombatSystemAttempt(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CombatSystemAttempt",
			"CombatSystemAttempt/Variant_Platforming",
			"CombatSystemAttempt/Variant_Platforming/Animation",
			"CombatSystemAttempt/Variant_Combat",
			"CombatSystemAttempt/Variant_Combat/AI",
			"CombatSystemAttempt/Variant_Combat/Animation",
			"CombatSystemAttempt/Variant_Combat/Gameplay",
			"CombatSystemAttempt/Variant_Combat/Interfaces",
			"CombatSystemAttempt/Variant_Combat/UI",
			"CombatSystemAttempt/Variant_SideScrolling",
			"CombatSystemAttempt/Variant_SideScrolling/AI",
			"CombatSystemAttempt/Variant_SideScrolling/Gameplay",
			"CombatSystemAttempt/Variant_SideScrolling/Interfaces",
			"CombatSystemAttempt/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
