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

#include "TapGestureRecognizer.generated.h"

/**
 * Recognizes tap gestures, including multi-tap (double tap, triple tap) gestures and multiple-touch taps (two-finger taps).
 */
UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class UTapGestureRecognizer : public UGestureRecognizerComponent
{
	GENERATED_BODY()
	
public:
	UTapGestureRecognizer();
	
	/** Minimum amount of time (in seconds) that the finger can be on the screen to trigger this gesture. Typically 0.0, but can be longer if a long-tap is desired */
	UPROPERTY(EditAnywhere, Category=Gestures)
	float MinimumTimeForTap;
	
	/** The maximum amount of time the finger can stay on the screen for it to count as a tap. */
	UPROPERTY(EditAnywhere, Category=Gestures)
	float MaximumTimeForTap;
	
	/** The minimum number of fingers that must have been used to register as a tap */
	UPROPERTY(EditAnywhere, Category=Gestures)
	int32 MinimumTouchCount;
	
	/** The maximum number of fingers that must have been used to register as a tap */
	UPROPERTY(EditAnywhere, Category=Gestures)
	int32 MaximumTouchCount;
	
	/** If checking for multiple taps (double-tap, triple-tap), set this value to a value higher than one */
	UPROPERTY(EditAnywhere, Category=Gestures)
	int32 MinimumNumberOfTaps;
	
	/** The maximum multiple tap (double, triple) that this recognizer will recognize. */
	UPROPERTY(EditAnywhere, Category=Gestures)
	int32 MaximumNumberOfTaps;
	
	/** The maximum distance in pixels that a finger can move and still count as a tap */
	UPROPERTY(EditAnywhere, Category=Gestures)
	int32 Tolerance;
	
	/** If looking for multi-taps, the maximum amount of time that can elapse from the start of one tap until the start of the next tap for them to be considered a single gesture **/
	UPROPERTY(EditAnywhere, Category=Gestures)
	float MaximumTimeBetweenTaps;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	int32 NumberOfFingersInTap;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	int32 NumberOfTaps;
	
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	FVector2D GetTapLocation() const;
	
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	bool TapWasOnLeftHalf();
	
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	bool TapWasOnRightHalf();
	
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	bool TapWasOnTopHalf();
	
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	bool TapWasOnBottomHalf();
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void InitializeComponent() override;
	
protected:
	FVector2D LastTapLocation;
	int32 TapCounts[EKeys::NUM_TOUCH_KEYS];
	float ToleranceSquared;
};
