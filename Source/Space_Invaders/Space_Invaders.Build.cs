// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Space_Invaders : ModuleRules
{
	public Space_Invaders(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
