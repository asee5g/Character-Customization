// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Customization : ModuleRules
{
	public Customization(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "Customization", "Slate", "SlateCore"});
	}
}
