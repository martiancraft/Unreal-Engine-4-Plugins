// =================================================================================================
//
//       ^                     ____________________
//      / \                   |                   |
//     / _ \                  | MartianCraft      |
//    ( (_) )                 | Public Code       |
//   /|  |  |\                |___________________|
//  //|__|__|\\
// (/   (|)   \)
//      \ /
//       v
//
//    Copyright 2015 MartianCraft. All rights reserved.
//    http://www.martiancraft.com       jeff@martiancraft.com
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//
// =================================================================================================

#pragma once
#include "ScalabilityFunctionLibrary.generated.h"


UENUM(BlueprintType)
enum class ENamedScalabilityLevel : uint8
{
	SL_LOW		UMETA(DisplayName="Low"),
	SL_MED		UMETA(DisplayName="Medium"),
	SL_HIGH		UMETA(DisplayName="High"),
	SL_EPIC		UMETA(DisplayName="Epic"),
	
	SL_NUM		UMETA(Hidden)
};
FString GetVictoryEnumAsString(ENamedScalabilityLevel EnumValue);



// ===================================================================================

/**
 * 
 */
UCLASS()
class SCALABILITYLIBRARY_API UScalabilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
	
	// ===============================================================================================
	// Screen Resolution
	// ===============================================================================================
	
	/** Provides a list of supported screen resolutions */
	UFUNCTION(BlueprintPure, Category = "Scalability")
	static bool GetSupportedScreenResolutions(TArray<FString>& Resolutions);

	/** Returns the current screen resolution as a string */
	UFUNCTION(BlueprintPure, Category = "Scalability")
	static FString GetScreenResolution();
	
	/** Detects if we're currently in full screen mode */
	UFUNCTION(BlueprintPure, Category = "Scalability")
	static bool IsFullscreen(bool& bIsFullScreen, bool& bIsWindowedFullScreen);
	
	/** Stores current resolution window mode in settings */
	UFUNCTION(BlueprintCallable, Category = "Scalability")
	static bool SetScreenResolution(const int32 Width, const int32 Height, const bool Fullscreen, bool WindowedFullScreen);
	
	/** Stores the current screen resolution if in full screen, or the window size if not. */
	UFUNCTION(BlueprintCallable, Category = "Scalability")
	static bool ChangeScreenResolution(const int32 Width, const int32 Height, const bool Fullscreen, bool WindowedFullScreen);
	
	// ===============================================================================================
	// Combined Quality
	// ===============================================================================================
	
	/** Gives access to all of the scalability settings at once. These are all based on a scale of 0-3 (0 being worst, 3 being best), except resolution which uses the scall 0-100 and represents a percentage of the current window or screen resolution.*/
	UFUNCTION(BlueprintCallable, Category = "Scalability")
	static bool GetVideoQualitySettings(int32& AntiAliasing, int32& Effects, int32& PostProcess, int32& Shadow, int32& Texture, int32& ViewDistance, int32& ResolutionScale);
	
	
	/* Sets video quality setting values. These are all based on a scale of 0-3 (0 being worst, 3 being best), except resolution which uses the scall 0-100 and represents a percentage of the current window or screen resolution. Unconnected pins will use the default value of -1, which will leave the setting at its current value.*/
	UFUNCTION(BlueprintCallable, Category = "Scalability")
	static bool SetVideoQualitySettings(const int32 AntiAliasing = -1, const int32 Effects = -1, const int32 PostProcess = -1, const int32 Shadow = -1, const int32 Texture = -1, const int32 ViewDistance = -1, const int32 ResolutionScale = 100);
	
	
	// ===============================================================================================
	// Anti-Aliasing
	// ===============================================================================================
	
	/* Returns the current anti-aliasing quality level as a number, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetAntiAliasingQuality(int32& AntiAliasingQuality);
	
	/* Returns the current anti-aliasing quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetAntiAliasingQualityAsName(ENamedScalabilityLevel& AntiAliasingQuality);
	
	/* Sets the anti-aliasing quality level, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool SetAntiAliasingQuality(const int32 AntiAliasingQuality);
	
	/* Sets the anti-aliasing quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	bool SetAntiAliasingQualityByName(const ENamedScalabilityLevel AntiAliasingQuality);
	
	// ===============================================================================================
	// Effects
	// ===============================================================================================
	
	/* Returns the current effects quality level as a number, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetEffectsQuality(int32& EffectsQuality);
	
	/* Returns the current effects quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetEffectsQualityAsName(ENamedScalabilityLevel& EffectsQuality);
	
	/* Sets the effects quality level, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool SetEffectsQuality(const int32 EffectsQuality);
	
	/* Sets the effects quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	bool SetEffectsQualityByName(const ENamedScalabilityLevel EffectsQuality);
	
	// ===============================================================================================
	// Post-Process
	// ===============================================================================================
	
	/* Returns the current post-process quality level as a number, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetPostProcessQuality(int32& PostProcessQuality);
	
	/* Returns the current post-process quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetPostProcessQualityAsName(ENamedScalabilityLevel& PostProcessQuality);
	
	/* Sets the effects post-process level, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool SetPostProcessQuality(const int32 PostProcessQuality);
	
	/* Sets the post-process quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	bool SetPostProcessQualityByName(const ENamedScalabilityLevel PostProcessQuality);
	
	// ===============================================================================================
	// Shadow
	// ===============================================================================================
	
	/* Returns the current shadow quality level as a number, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetShadowQuality(int32& ShadowQuality);
	
	/* Returns the current shadow quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetShadowQualityAsName(ENamedScalabilityLevel& ShadowQuality);
	
	/* Sets the shadow quality level, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool SetShadowQuality(const int32 ShadowQuality);
	
	/* Sets the shadow quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	bool SetShadowQualityByName(const ENamedScalabilityLevel ShadowQuality);
	
	// ===============================================================================================
	// Texture
	// ===============================================================================================
	
	/* Returns the current texture quality level as a number, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetTextureQuality(int32& TextureQuality);
	
	/* Returns the current texture quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetTextureQualityAsName(ENamedScalabilityLevel& TextureQuality);
	
	/* Sets the texture quality level, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool SetTextureQuality(const int32 TextureQuality);
	
	/* Sets the texture quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	bool SetTextureQualityByName(const ENamedScalabilityLevel TextureQuality);
	
	// ===============================================================================================
	// View Distance
	// ===============================================================================================
	
	/* Returns the current view distance quality level as a number, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetViewDistanceQuality(int32& ViewDistanceQuality);
	
	/* Returns the current view distance quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetViewDistanceQualityAsName(ENamedScalabilityLevel& ViewDistanceQuality);
	
	/* Sets the view distance quality level, 0-3 */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool SetViewDistanceQuality(const int32 ViewDistanceQuality);
	
	/* Sets the view distance quality level by name: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	bool SetViewDistanceQualityByName(const ENamedScalabilityLevel ViewDistanceQuality);
	
	// ===============================================================================================
	// Resolution Scale
	// ===============================================================================================
	
	/* Returns the current resolution scale. Will be a value from 1-100 representing the percentage of the current screen or window size that the engine is currently rendering at. Lower numbers decrease quality but increase performance. */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool GetResolutionScale(int32& ResolutionScale);

	/* Set the current resolution scale. Should be value from 1-100, though you would rarely want to go lower than 50.  Represents the percentage of the current screen or window size that the engine is currently rendering at. Lower numbers decrease quality but increase performance. */
	UFUNCTION(BlueprintCallable, Category="Scalability")
	static bool SetResolutionScale(const int32 ResolutionScale);
	
	// ===============================================================================================
	// VSync
	// ===============================================================================================
	
	/** Identifies whether v-sync is on or off */
	UFUNCTION(BlueprintPure, Category = "Scalability")
	static bool IsVSyncEnabled(bool& VSyncEnabled);
	
	/** Turn vsync on or off */
	UFUNCTION(BlueprintCallable, Category = "Scalability")
	static bool SetVSyncEnabled(const bool VSync);
	
	// ===============================================================================================
	// General
	// ===============================================================================================
	
	/** Confirm and save current video mode (resolution and fullscreen/windowed) as well as quality settings */
	UFUNCTION(BlueprintCallable, Category = "Scalability")
	static bool SaveVideoModeAndQuality();
	
	/** Reverts video settings to the default values provided in DefaultGameUserSettings.ini */
	UFUNCTION(BlueprintCallable, Category = "Scalability")
	static bool RevertVideoMode();
	
	/** Set's video quality based on a named scalability level: low, medium, high, or epic */
	UFUNCTION(BlueprintCallable, Category = "Scalability")
	static bool SetOverallVideoQualityByLevel(const ENamedScalabilityLevel NewLevel);
	
	/** Autodetects and sets all quality settings by running hardware benchmark. */
	UFUNCTION(BlueprintCallable, Category = "Scalability")
	static bool AutoSetQualityLevel();
	
	// ===============================================================================================
	// Private
	// ===============================================================================================
	
private:
	
	static class UGameUserSettings* GetGameUserSettings();
	
};
