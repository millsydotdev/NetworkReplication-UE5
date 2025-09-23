// Copyright © 2025 Millsy.dev. All Rights Reserved.
//
// NetworkReplicationSubsystem.Build.cs
// Build configuration for the Network Replication Subsystem plugin.

using UnrealBuildTool;

public class NetworkReplicationSubsystem : ModuleRules
{
	public NetworkReplicationSubsystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
			}
		);
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
		);
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"NetCore",
				"Niagara",
				"Chooser",
				"AnimationCore",
				"PoseSearch"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
			}
		);
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}