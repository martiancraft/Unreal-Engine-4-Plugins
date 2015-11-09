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
#include "GestureMathLibrary.generated.h"

/**
 * A set of blueprint nodes for doing screen-related math, primarily for handling touch and gestures on mobile devices.
 */
UCLASS()
class  UGestureMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Calculates the angle between two lines in 2D space
	 *
	 * @param	Line1Start	- The start point of the first line
	 * @param	Line1End - The end point of the first line
	 * @param	Line2Start - The start point of the second line
	 * @param	Line2End - The end point of the second line
	 * @result	The angle between the two lines in Radians
	 */
	UFUNCTION(BlueprintPure, Category="Math|Gesture Utils")
	static float AngleBetweenLines(const FVector2D& Line1Start, const FVector2D& Line1End, const FVector2D& Line2Start, const FVector2D& Line2End);
	
	/**
	 * Returns `true` if a specified `FVector2D1 is on the left side of the screen */
	
	UFUNCTION(BlueprintPure, Category="Math|Gesture Utils")
	static bool PointOnLeftHalfOfScreen(FVector2D Point);
	
	/** Returns `true` if a specified FVector2D is on the right half of the screen */
	UFUNCTION(BlueprintPure, Category="Math|Gesture Utils")
	static bool PointOnRightHalfOfScreen(FVector2D Point);
	
	/** Returns `true` if a specified FVector2D is on the top half of the screen */
	UFUNCTION(BlueprintPure, Category="Math|Gesture Utils")
	static bool PointOnTopHalfOfScreen(FVector2D Point);
	
	/** Returns `true` if a specified FVector2D is on the bottom half of the screen */
	UFUNCTION(BlueprintPure, Category="Math|Gesture Utils")
	static bool PointOnBottomHalfOfScreen(FVector2D Point);
	
	/** Gesture values typically are based on points, not pixels. On a Retina or other HighDPI screen, you typically need your tolerances to be considerably higher because moving your finger the same distance will result in a lot more pixels. This function will return the scaling factor for the current device's screen to normalize to a standard scale */
	UFUNCTION(BlueprintPure, Category="Math|Gesture Utils")
	static float GetScalingFactorForScreen();
	
	UFUNCTION(BlueprintPure, Category="Math|Gesture Utils")
	/** Converts a float value to account for the resolution of the screen (1.0 = ~72DPI) */
	static float ScaleFloatForScreen(float Value);
	
	UFUNCTION(BlueprintPure, Category="Math|Gesture Utils")
	/** Converts an FVector value to account for the resolution of the screen (1.0 = ~72DPI) */
	static FVector2D ScaleVector2DForScreen(FVector2D Value);
	
};
