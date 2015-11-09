// Some copyright should be here...

using UnrealBuildTool;

public class MobileGestureRecognizerPlugin : ModuleRules
{
	public MobileGestureRecognizerPlugin(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] 
			{
				"MobileGestureRecognizerPlugin/Public"
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] 
			{
				"MobileGestureRecognizerPlugin/Private",

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
