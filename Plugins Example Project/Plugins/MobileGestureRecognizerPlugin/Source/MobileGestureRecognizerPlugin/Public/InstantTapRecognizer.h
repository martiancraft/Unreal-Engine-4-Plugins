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

#include "InstantTapRecognizer.generated.h"

class UInstantTapRecognizer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGestureStarted, UInstantTapRecognizer *, Recognizer, float, DeltaTime);


/**
 * The regular `UTapGestureRecognizer` has a slight delay built in after a finger has left the screen so that it can detect multiple taps (double-taps, triple-taps) without triggering the delegate multiple times (e.g. no single tap delegate call when double tapped). Sometimes, in games, however, you want to know the second any finger touches the screen so that there's no delay. This simple gesture recognizer tells you immediately if a finger touches the screen or is removed from the scren. All it tells you is which finger where it touched. That touch may end up being part of another gesture, so it's your responsibility to make sure the tap doesn't have any unintended side effects. The GestureEndedDelegate is used to tell the delegate when any finger has been taken off the screen, and GestureStartedDelegate is used to tell the delegate when a finger has first touched the screen.
 */
UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class UInstantTapRecognizer : public UGestureRecognizerComponent
{
	GENERATED_BODY()
	
public:
	/** Use by delegates to identify which finger touched the screen. Only guaranteed to be correct during the delegate call. */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Gestures|Result")
	int32 WhichFinger;
	
	/** Used by delegates to get the location of the touch. Only guaranteed to be correct during the delegate call. */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Gestures|Result")
	FVector2D TouchLocation;
	
	/** Delegate function called when a finger first touches the screen.
	 */
	UPROPERTY(BlueprintAssignable, Category=Gestures)
	FGestureEnded GestureBeganDelegate;
	
	
	virtual void TouchBegan(int32 FingerIndex, FVector2D Position) override;
	virtual void TouchEnded(int32 FingerIndex) override;
	
};
