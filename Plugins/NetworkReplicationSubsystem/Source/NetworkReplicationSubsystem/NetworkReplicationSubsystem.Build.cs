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
		
		// Use modern UE5.6 include order
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		
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