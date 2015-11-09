// 2015  MartianCraft, LLC, See header file for license & copyright notice

#include "OffscreenIndicatorPrivatePCH.h"



#define LOCTEXT_NAMESPACE "FOffscreenIndicatorModule"

void FOffscreenIndicatorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FOffscreenIndicatorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOffscreenIndicatorModule, OffscreenIndicator)