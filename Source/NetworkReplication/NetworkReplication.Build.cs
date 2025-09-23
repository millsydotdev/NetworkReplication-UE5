using UnrealBuildTool;

public class NetworkReplication : ModuleRules
{
	public NetworkReplication(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"HeadMountedDisplay",
			"UMG",
			"Slate",
			"SlateCore",
			"Niagara",
			"NiagaraCore",
			"AudioPlatformConfiguration"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"ToolMenus"
		});
	}
}
