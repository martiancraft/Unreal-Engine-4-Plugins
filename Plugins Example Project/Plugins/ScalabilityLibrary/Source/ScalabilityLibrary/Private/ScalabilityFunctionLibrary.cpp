// 2015  MartianCraft, LLC, See header file for license & copyright notice

#include "ScalabilityLibraryPrivatePCH.h"

#define MIN_SCREEN_WIDTH 1024
#define MIN_SCREEN_HEIGHT 768

FString GetVictoryEnumAsString(ENamedScalabilityLevel EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENamedScalabilityLevel"), true);
	if(!EnumPtr) return FString("Invalid");

	return EnumPtr->GetEnumName((int32)EnumValue);
}



// ===============================================================================================
// Screen Resolution
// ===============================================================================================

bool UScalabilityFunctionLibrary::GetSupportedScreenResolutions(TArray<FString>& Resolutions)
{
	FScreenResolutionArray ResolutionsArray;
	
	if(RHIGetAvailableResolutions(ResolutionsArray, true))  // needs the "RHI" dependency
	{
		for(const FScreenResolutionRHI& Resolution : ResolutionsArray)
		{
			if(Resolution.Width < MIN_SCREEN_WIDTH || Resolution.Height < MIN_SCREEN_HEIGHT)
			{
				continue;
			}
			
			FString Str = FString::FromInt(Resolution.Width) + "x" + FString::FromInt(Resolution.Height);
			Resolutions.AddUnique(Str);
		}
		
		return true;
	}
	
	return false;  // failed to obtain screen resolutions
}

FString UScalabilityFunctionLibrary::GetScreenResolution()
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return FString("");
	}
	
	FIntPoint Resolution = Settings->GetScreenResolution();
	return FString::FromInt(Resolution.X) + "x" + FString::FromInt(Resolution.Y);
}

bool UScalabilityFunctionLibrary::IsFullscreen(bool& bIsFullScreen, bool& bIsWindowedFullScreen)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	bIsFullScreen = Settings->GetFullscreenMode() == EWindowMode::Fullscreen || Settings->GetFullscreenMode() == EWindowMode::WindowedFullscreen;
	bIsWindowedFullScreen = Settings->GetFullscreenMode() == EWindowMode::WindowedFullscreen;
	
	return true;
}

bool UScalabilityFunctionLibrary::SetScreenResolution(const int32 Width, const int32 Height, bool Fullscreen, bool WindowedFullScreen)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->SetScreenResolution(FIntPoint(Width, Height));
	Settings->SetFullscreenMode(Fullscreen ? (WindowedFullScreen ? EWindowMode::WindowedFullscreen : EWindowMode::Fullscreen): EWindowMode::Windowed);
	return true;
}

bool UScalabilityFunctionLibrary::ChangeScreenResolution(const int32 Width, const int32 Height, const bool Fullscreen, bool WindowedFullScreen)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	EWindowMode::Type WindowMode = Fullscreen ? (WindowedFullScreen ? EWindowMode::WindowedFullscreen : EWindowMode::Fullscreen): EWindowMode::Windowed;
	Settings->RequestResolutionChange(Width, Height, WindowMode, false);
	return true;
}

// ===============================================================================================
// Combined Quality
// ===============================================================================================

bool UScalabilityFunctionLibrary::GetVideoQualitySettings(int32& AntiAliasing, int32& Effects, int32& PostProcess,
												  int32& Shadow, int32& Texture, int32& ViewDistance, int32& ResolutionScale)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	AntiAliasing = Settings->ScalabilityQuality.AntiAliasingQuality;
	Effects = Settings->ScalabilityQuality.EffectsQuality;
	PostProcess = Settings->ScalabilityQuality.PostProcessQuality;
	Shadow = Settings->ScalabilityQuality.ShadowQuality;
	Texture = Settings->ScalabilityQuality.TextureQuality;
	ViewDistance = Settings->ScalabilityQuality.ViewDistanceQuality;
	
	ResolutionScale = Settings->ScalabilityQuality.ResolutionQuality;
	
	return true;
}
//
bool UScalabilityFunctionLibrary::SetVideoQualitySettings(const int32 AntiAliasing, const int32 Effects, const int32 PostProcess,
												const int32 Shadow, const int32 Texture, const int32 ViewDistance, const int32 ResolutionScale)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	bool ChangedAnything = false;
	
	if (AntiAliasing != -1)
	{
		Settings->ScalabilityQuality.AntiAliasingQuality = FMath::Clamp(AntiAliasing, 0, 3);
		ChangedAnything = true;
	}
	
	if (Effects != -1)
	{
		Settings->ScalabilityQuality.EffectsQuality = FMath::Clamp(Effects, 0, 3);
		ChangedAnything = true;
	}
	
	if (PostProcess != -1)
	{
		Settings->ScalabilityQuality.PostProcessQuality = FMath::Clamp(PostProcess, 0, 3);
		ChangedAnything = true;
	}
	
	if (Shadow != -1)
	{
		Settings->ScalabilityQuality.ShadowQuality = FMath::Clamp(Shadow, 0, 3);
		ChangedAnything = true;
	}
	
	if (Texture != -1)
	{
		Settings->ScalabilityQuality.TextureQuality = FMath::Clamp(Texture, 0, 3);
		ChangedAnything = true;
	}
	
	if (ViewDistance != -1)
	{
		Settings->ScalabilityQuality.ViewDistanceQuality = FMath::Clamp(ViewDistance, 0, 3);
		ChangedAnything = true;
	}
	
	if (ResolutionScale != -1)
	{
		Settings->ScalabilityQuality.ResolutionQuality = FMath::Clamp(ResolutionScale, 0, 100);
		ChangedAnything = true;
	}
	
	
	return ChangedAnything;
}

// ===============================================================================================
// Anti-Aliasing
// ===============================================================================================

bool UScalabilityFunctionLibrary::GetAntiAliasingQuality(int32& AntiAliasingQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	AntiAliasingQuality = Settings->ScalabilityQuality.AntiAliasingQuality;
	return true;
}

bool UScalabilityFunctionLibrary::GetAntiAliasingQualityAsName(ENamedScalabilityLevel& AntiAliasingQuality)
{
	int32 AAQualityNumber;
	bool Result = GetAntiAliasingQuality(AAQualityNumber);
	AntiAliasingQuality = (ENamedScalabilityLevel)AAQualityNumber;
	return Result;
}

bool UScalabilityFunctionLibrary::SetAntiAliasingQuality(const int32 AntiAliasingQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ScalabilityQuality.AntiAliasingQuality = FMath::Clamp(AntiAliasingQuality, 0, 3);
	return true;
}

bool UScalabilityFunctionLibrary::SetAntiAliasingQualityByName(const ENamedScalabilityLevel AntiAliasingQuality)
{
	return SetAntiAliasingQuality((int32)AntiAliasingQuality);
}

// ===============================================================================================
// Effects
// ===============================================================================================

bool UScalabilityFunctionLibrary::GetEffectsQuality(int32& EffectsQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	EffectsQuality = Settings->ScalabilityQuality.EffectsQuality;
	return true;
}

bool UScalabilityFunctionLibrary::GetEffectsQualityAsName(ENamedScalabilityLevel& EffectsQuality)
{
	int32 EffectsQualityNumber;
	bool Result = GetEffectsQuality(EffectsQualityNumber);
	EffectsQuality = (ENamedScalabilityLevel)EffectsQualityNumber;
	return Result;
}

bool UScalabilityFunctionLibrary::SetEffectsQuality(const int32 EffectsQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ScalabilityQuality.EffectsQuality = FMath::Clamp(EffectsQuality, 0, 3);
	return true;
}

bool UScalabilityFunctionLibrary::SetEffectsQualityByName(const ENamedScalabilityLevel EffectsQuality)
{
	return SetEffectsQuality((int32)EffectsQuality);
}

// ===============================================================================================
// Post-Process
// ===============================================================================================

bool UScalabilityFunctionLibrary::GetPostProcessQuality(int32& PostProcessQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	PostProcessQuality = Settings->ScalabilityQuality.PostProcessQuality;
	return true;
}

bool UScalabilityFunctionLibrary::GetPostProcessQualityAsName(ENamedScalabilityLevel& PostProcessQuality)
{
	int32 PPQualityNumber;
	bool Result = GetPostProcessQuality(PPQualityNumber);
	PostProcessQuality = (ENamedScalabilityLevel)PPQualityNumber;
	return Result;
}

bool UScalabilityFunctionLibrary::SetPostProcessQuality(const int32 PostProcessQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ScalabilityQuality.PostProcessQuality = FMath::Clamp(PostProcessQuality, 0, 3);
	return true;
}

bool UScalabilityFunctionLibrary::SetPostProcessQualityByName(const ENamedScalabilityLevel PostProcessQuality)
{
	return SetPostProcessQuality((int32)PostProcessQuality);
}

// ===============================================================================================
// Shadow
// ===============================================================================================

bool UScalabilityFunctionLibrary::GetShadowQuality(int32& ShadowQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	ShadowQuality = Settings->ScalabilityQuality.ShadowQuality;
	return true;
}

bool UScalabilityFunctionLibrary::GetShadowQualityAsName(ENamedScalabilityLevel& ShadowQuality)
{
	int32 ShadowQualityNumber;
	bool Result = GetShadowQuality(ShadowQualityNumber);
	ShadowQuality = (ENamedScalabilityLevel)ShadowQualityNumber;
	return Result;
}

bool UScalabilityFunctionLibrary::SetShadowQuality(const int32 ShadowQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ScalabilityQuality.ShadowQuality = FMath::Clamp(ShadowQuality, 0, 3);
	return true;
}

bool UScalabilityFunctionLibrary::SetShadowQualityByName(const ENamedScalabilityLevel ShadowQuality)
{
	return SetShadowQuality((int32)ShadowQuality);
}

// ===============================================================================================
// Texture
// ===============================================================================================

bool UScalabilityFunctionLibrary::GetTextureQuality(int32& TextureQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	TextureQuality = Settings->ScalabilityQuality.TextureQuality;
	return true;
}

bool UScalabilityFunctionLibrary::GetTextureQualityAsName(ENamedScalabilityLevel& TextureQuality)
{
	int32 TextureQualityNumber;
	bool Result = GetTextureQuality(TextureQualityNumber);
	TextureQuality = (ENamedScalabilityLevel)TextureQualityNumber;
	return Result;
}

bool UScalabilityFunctionLibrary::SetTextureQuality(const int32 TextureQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ScalabilityQuality.TextureQuality = FMath::Clamp(TextureQuality, 0, 3);
	return true;
}

bool UScalabilityFunctionLibrary::SetTextureQualityByName(const ENamedScalabilityLevel TextureQuality)
{
	return SetTextureQuality((int32)TextureQuality);
}

// ===============================================================================================
// ViewDistance
// ===============================================================================================

bool UScalabilityFunctionLibrary::GetViewDistanceQuality(int32& ViewDistanceQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	ViewDistanceQuality = Settings->ScalabilityQuality.ViewDistanceQuality;
	return true;
}

bool UScalabilityFunctionLibrary::GetViewDistanceQualityAsName(ENamedScalabilityLevel& ViewDistanceQuality)
{
	int32 ViewDistanceQualityNumber;
	bool Result = GetViewDistanceQuality(ViewDistanceQualityNumber);
	ViewDistanceQuality = (ENamedScalabilityLevel)ViewDistanceQualityNumber;
	return Result;
}

bool UScalabilityFunctionLibrary::SetViewDistanceQuality(const int32 ViewDistanceQuality)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ScalabilityQuality.ViewDistanceQuality = FMath::Clamp(ViewDistanceQuality, 0, 3);
	return true;
}

bool UScalabilityFunctionLibrary::SetViewDistanceQualityByName(const ENamedScalabilityLevel ViewDistanceQuality)
{
	return SetViewDistanceQuality((int32)ViewDistanceQuality);
}

// ===============================================================================================
// Resolution Scale
// ===============================================================================================

bool UScalabilityFunctionLibrary::GetResolutionScale(int32& ResolutionScale)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	ResolutionScale = Settings->ScalabilityQuality.ResolutionQuality;
	return true;
}

bool UScalabilityFunctionLibrary::SetResolutionScale(const int32 ResolutionScale)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ScalabilityQuality.ResolutionQuality = FMath::Clamp(ResolutionScale, 0, 100);
	return true;
	
}

// ===============================================================================================
// VSync
// ===============================================================================================

bool UScalabilityFunctionLibrary::IsVSyncEnabled(bool& VSyncEnabled)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}

	VSyncEnabled = Settings->IsVSyncEnabled();
	return true;
}

bool UScalabilityFunctionLibrary::SetVSyncEnabled(const bool VSync)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->SetVSyncEnabled(VSync);
	return true;
}

// ===============================================================================================
// General
// ===============================================================================================

bool UScalabilityFunctionLibrary::SaveVideoModeAndQuality()
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ConfirmVideoMode();
	Settings->ApplyNonResolutionSettings();
	Settings->SaveSettings();
	return true;
}

bool UScalabilityFunctionLibrary::RevertVideoMode()
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->RevertVideoMode();
	return true;
}

bool UScalabilityFunctionLibrary::SetOverallVideoQualityByLevel(const ENamedScalabilityLevel NewLevel)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ScalabilityQuality.SetFromSingleQualityLevel((int32)NewLevel);
	return true;
}

bool UScalabilityFunctionLibrary::AutoSetQualityLevel()
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if(!Settings)
	{
		return false;
	}
	
	Settings->ScalabilityQuality = Scalability::BenchmarkQualityLevels(1.0);
	return true;
}

// ===============================================================================================
// Private
// ===============================================================================================

UGameUserSettings* UScalabilityFunctionLibrary::GetGameUserSettings()
{
	if(GEngine != nullptr)
	{
		return GEngine->GameUserSettings;
	}
	
	return nullptr;
}