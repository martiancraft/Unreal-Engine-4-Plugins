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

#include "PanGestureRecognizer.generated.h"

/**
 *  Recognizes pan gestures - one or more fingers moving around the screen
 */
UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class UPanGestureRecognizer : public UDynamicGestureRecognizer
{
	GENERATED_BODY()
	UPanGestureRecognizer();
	
public:
	/** The minimum number of fingers that must be touching the screen in order for the delegate to be notified */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gestures)
	int32 MinimumTouchCount;
	
	/** The maximum number of fingers that can be down for the delegate to be notified */
	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category=Gestures)
	int32 MaximumTouchCount;
	
	/** Access to the position of each key for the delegate method */
	UPROPERTY(VisibleInstanceOnly, Category="Gestures|Result")
	FVector2D TouchPoints[EKeys::NUM_TOUCH_KEYS];
	
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	TArray<FVector2D> GetTouchPoints();
	
	/** Returns the screen coordinate position of the first touch */
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	FVector2D FirstFingerTouchLocation();
	
	/** Allows delegate access to the number of fingers currently touching the screen */
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	int32 GetTouchCount();
	
	/** Convenience function to retrieve the distance moved by any finger since the last delegate call. */
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	FVector2D LastMoveDistanceForTouch(int32 Touch);
	
	/** Convenience function to retrieve the distance moved by any finger since the last delegate call. his value is adjusted for screen resolution and returned in points not pixels */
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	FVector2D LastMoveDistanceInPointsForTouch(int32 Touch);
	
	/** Convenience function to retrieve the distance moved by the first finger since the last delegate call */
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	FVector2D LastMoveDistanceForFirstTouch();
	
	/** Convenience function to retrieve the distance moved by the first finger since the last delegate call. This value is adjusted for screen resolution and returned in points not pixels. */
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	FVector2D LastMoveDistanceForFirstTouchInPoints();
	
	
	
protected:
	virtual void DetectGestures(float DeltaTime) override;
	virtual void GestureFinished(float DeltaTime) override;
	virtual void ResetGesture(void) override;
	
private:
	bool bGestureBegan;
	
};
