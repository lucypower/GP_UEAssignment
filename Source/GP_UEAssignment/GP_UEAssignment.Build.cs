// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GP_UEAssignment : ModuleRules
{
	public GP_UEAssignment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
