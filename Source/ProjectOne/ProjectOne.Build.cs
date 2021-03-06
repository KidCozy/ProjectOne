// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectOne : ModuleRules
{
	public ProjectOne(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
            "HeadMountedDisplay", "Paper2D", "UMG", "NavigationSystem", "AIModule", "AkAudio" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        DynamicallyLoadedModuleNames.AddRange(new string[] {  });
    }
}
