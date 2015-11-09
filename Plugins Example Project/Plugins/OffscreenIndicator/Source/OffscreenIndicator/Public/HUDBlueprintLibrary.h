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


#include "HUDBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class OFFSCREENINDICATOR_API UHUDBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Converts a world location to screen position for HUD drawing. This differs from the results of FSceneView::WorldToScreen in that it returns a position along the edge of the screen for offscreen locations
	 *
	 * @param		InLocation	- The world space location to be converted to screen space
	 * @param		EdgePercent - How close to the edge of the screen, 1.0 = at edge, 0.0 = at center of screen. .9 or .95 is usually desirable
	 * @outparam	OutScreenPosition - the screen coordinates for HUD drawing
	 * @outparam	OutRotationAngleDegrees - The angle to rotate a hud element if you want it pointing toward the offscreen indicator, 0° if onscreen
	 * @outparam	bIsOnScreen - True if the specified location is in the camera view (may be obstructed)
	 */
	UFUNCTION(BlueprintPure, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext), Category="Republic Sniper|HUD|Util")
	static void FindScreenLocationForWorldLocation(UObject* WorldContextObject, const FVector& InLocation, const float EdgePercent,  FVector2D& OutScreenPosition, float& OutRotationAngleDegrees, bool &bIsOnScreen);
	
	/**
	 * Identifies whether a given world location is currently on screen and within a specified range of the local player. 
	 *
	 * @param		InLocation	- The world space location to be converted to screen space
	 * @param		InMaxDistance - The maximum distance from the camera to consider
	 * @result		True if the specified location is in the camera view (may be obstructed)
	 */
	UFUNCTION(BlueprintPure, meta=(WorldContext="WorldContextObject", CallableWithoutWorldContext), Category="Republic Sniper|HUD|Util")
	static bool IsPointOnScreenWithinDistance(UObject* WorldContextObject, const FVector& InWorldLocation, const float& InMaxDistance);
	
	/**
	 * Returns the name of the current map. Useful for restarting a level
	 */
	UFUNCTION(BlueprintPure, meta=(WorldContext="WorldContextObject"), Category="Republic Sniper|HUD|Util")
	static FString GetCurrentLevelName(UObject* WorldContextObject);
	
	/** 
	 * Returns the 2D bounding box for an actor for highlighting in a HUD 
	 *
	 * @param		Actor		The actor you want the 2D bounding box for
	 * @outparam	OutCenter	The center of the actor in screen coordinates
	 * @outparam	OutSize		The size of hte actor in screen pixels
	 */
	UFUNCTION(BlueprintPure, meta=(WorldContext="WorldContextObject"), Category="Republic Sniper|HUD|Util")
	static void Projected2DBoundsBoxForActor(UObject* WorldContextObject, const AActor *Actor, FVector2D &OutCenter, FVector2D &OutSize);
	
	/**
	 * Returns the 2D bounding box for a box component for highlighting in a HUD
	 *
	 * @param		Component	The box component you want the 2D bounding box for
	 * @outparam	OutCenter	The center of the actor in screen coordinates
	 * @outparam	OutSize		The size of hte actor in screen pixels
	 */
	UFUNCTION(BlueprintPure, meta=(WorldContext="WorldContextObject"), Category="Republic Sniper|HUD|Util")
	static void Projected2DBoundsBoxForBoxComponent(UObject* WorldContextObject, const UBoxComponent *Component, FVector2D &OutCenter, FVector2D &OutSize);
	
	/**
	 * Returns a 2D bounding box given an origin and an extents
	 *
	 * @param		Origin		The world space origin
	 * @param		Extents		The extents
	 * @outparam	OutCenter	The center of the actor in screen coordinates
	 * @outparam	OutSize		The size of hte actor in screen pixels
	 */
	UFUNCTION(BlueprintPure, meta=(WorldContext="WorldContextObject"), Category="Republic Sniper|HUD|Util")
	static void Projected2DBoundsWithOriginAndExtent(UObject* WorldContextObject, FVector Origin, FVector Extents,FVector2D &OutCenter, FVector2D &OutSize);
	
};
