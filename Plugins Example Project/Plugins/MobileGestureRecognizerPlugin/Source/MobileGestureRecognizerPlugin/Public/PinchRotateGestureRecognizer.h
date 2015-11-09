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

#include "PinchRotateGestureRecognizer.generated.h"

/**
 * Gesture recognizer for two-finger pinch and rotate gestures
 */
UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class MOBILEGESTURERECOGNIZERPLUGIN_API UPinchRotateGestureRecognizer : public UDynamicGestureRecognizer
{
	GENERATED_BODY()
	UPinchRotateGestureRecognizer();
	
public:
	
	/** The smallest change in angle (degrees) between two fingers before the gesture is recognized as rotating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gestures)
	float MinimumAngleChangeForRotate;
	
	/** The smallest change in distance (pixels) between two fingers before the gesture is recognized as a pinch */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gestures)
	float MinimumDistanceChangeForPinch;
	
	/** The angle change since the last GestureMoved delegate call */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	float DeltaRotationDegrees;
	
	/** The angle change (degrees) since the gesture started. Note, any time the number of fingers being used stops being two, that resets the accumulation. When you go back to two fingers, it's treated as a new gesture, even if all fingers haven't been taken off the device */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	float AccumulatedAngleChange;
	
	/** The change in distance in pixels between the two touches since the last GestureMoved delegate call */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	float DeltaDistancePixels;
	
	/** The total change in distance in pixels since the pinch started */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	float AccumulatedDistanceChange;
	
	/** Whether a pinch has started. Delegate will only get notified if this or bIsRotating is true */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	bool bIsPinching;
	
	/** Whether a rotate has started. Delegate will only get notified if this or bIsPinching are true */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	bool bIsRotating;
	
	
protected:
	virtual void DetectGestures(float DeltaTime) override;
	virtual void GestureFinished(float DeltaTime) override;
	virtual void ResetGesture(void) override;
	
private:

};
