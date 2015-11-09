// Some copyright should be here...

using UnrealBuildTool;

public class OffscreenIndicator : ModuleRules
{
	public OffscreenIndicator(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"OffscreenIndicator/Public"
				
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"OffscreenIndicator/Private",
				
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
		new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
		}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate", "SlateCore"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
