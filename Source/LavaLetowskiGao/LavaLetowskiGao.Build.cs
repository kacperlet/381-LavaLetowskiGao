// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LavaLetowskiGao : ModuleRules
{
	public LavaLetowskiGao(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"LavaLetowskiGao",
			"LavaLetowskiGao/Variant_Platforming",
			"LavaLetowskiGao/Variant_Platforming/Animation",
			"LavaLetowskiGao/Variant_Combat",
			"LavaLetowskiGao/Variant_Combat/AI",
			"LavaLetowskiGao/Variant_Combat/Animation",
			"LavaLetowskiGao/Variant_Combat/Gameplay",
			"LavaLetowskiGao/Variant_Combat/Interfaces",
			"LavaLetowskiGao/Variant_Combat/UI",
			"LavaLetowskiGao/Variant_SideScrolling",
			"LavaLetowskiGao/Variant_SideScrolling/AI",
			"LavaLetowskiGao/Variant_SideScrolling/Gameplay",
			"LavaLetowskiGao/Variant_SideScrolling/Interfaces",
			"LavaLetowskiGao/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
