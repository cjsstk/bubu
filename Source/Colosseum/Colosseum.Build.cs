// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class Colosseum : ModuleRules
{
	public Colosseum(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "GameplayTasks", "NavigationSystem", "AIModule" });

        PrivateIncludePaths.AddRange(new string[]{
            "Colosseum"
        });

    }
}
