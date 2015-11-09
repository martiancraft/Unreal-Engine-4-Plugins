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

#include "SwipeGestureRecognizer.generated.h"

/** The supported types of swipes this recognizer can identify */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ESwipeType : uint8
{
	SwipeNone			UMETA(DisplayName="No Swipe"),
	SwipeLeft			UMETA(DisplayName="Swipe Left"),
	SwipeRight			UMETA(DisplayName="Swipe Right"),
	SwipeUp				UMETA(DisplayName="Swipe Up"),
	SwipeDown			UMETA(DisplayName="Swipe Down"),
	SwipeUpRight		UMETA(DisplayName="Diagonal Swipe Up and Right"),
	SwipeUpLeft			UMETA(DisplayName="Diagonal Swipe Up and Left"),
	SwipeDownRight		UMETA(DisplayName="Diagonal Swipe Down and Right"),
	SwipeDownLeft		UMETA(DisplayName="Diagonal Swipe Down and Left"),
	SwipeFromLeftEdge	UMETA(DisplayName="Swipe in from Left Edge"),
	SwipeFromTopEdge	UMETA(DisplayName="Swipe down from Top Edge"),
	SwipeFromRightEdge	UMETA(DisplayName="Swipe in from Right Edge"),
	SwipeFromBottomEdge UMETA(DisplayName="Swipe up from Bottom Edge")
};

USTRUCT()
struct FGestureSupportedSwipeTypes
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeLeft					:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeRight					:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeUp						:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeDown					:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeDiagonalUpRight		:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeDiagonalUpLeft			:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeDiagonalDownRight		:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeDiagonalDownLeft		:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeFromLeftEdge			:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeFromRightEdge			:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeFromTopEdge			:1;
	
	UPROPERTY(EditAnywhere)
	uint16 bSupportsSwipeFromBottomEdge			:1;
	
	FGestureSupportedSwipeTypes()
	{
		bSupportsSwipeLeft = true;
		bSupportsSwipeRight = true;
		bSupportsSwipeUp = true;
		bSupportsSwipeDown = true;
		
		bSupportsSwipeDiagonalUpRight = false;
		bSupportsSwipeDiagonalUpLeft = false;
		bSupportsSwipeDiagonalDownRight = false;
		bSupportsSwipeDiagonalDownLeft = false;
		
		bSupportsSwipeFromLeftEdge = true;
		bSupportsSwipeFromRightEdge = true;
		bSupportsSwipeFromTopEdge = true;
		bSupportsSwipeFromBottomEdge = true;
	}
};

/**
 * A gesture recognizer component to detect swipes. This recognizer does not support the GestureMoved delegate call. Delegates are only notified when a swipe has been detected. If delegates need notice during a swipe, a pan gesture recognizer should be used as well.
 */
UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class USwipeGestureRecognizer : public UGestureRecognizerComponent
{
	GENERATED_BODY()
	USwipeGestureRecognizer();
	
public:
	
	/** The minimum length of a swipe to register as a swipe */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gestures)
	float MinimumSwipeDistance;
	
	/** How far the gesture can travel in the 'wrong' direction (e.g. up/down for a horizontal swipe) before the gesture no longer counts as a swipe. Only use for up/down/left/right, not diagonal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gestures)
	float Tolerance;
	
	/** Which types of swipes this recognizer should look for */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gestures|Supported Swipes")
	FGestureSupportedSwipeTypes SupportedSwipes;
	
	/** The maximum amount of time the gesture can take, from touch down to touch up, to count as a swipe */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gestures)
	float MaximumGestureDuration;
	
	/** The minimum number of fingers that must touch the screen during the swipe for it to count */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gestures)
	int32 MinimumTouches;
	
	/** The maximum number of fingers that can touch the screen during the swipe for it to count */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gestures)
	int32 MaximumTouches;
	
	/** When a delegate is informed of a swipe, it can query this field to identify which type of swipe was detected */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	ESwipeType SwipeType;
	
	UFUNCTION(BlueprintCallable, Category="Gestures|Result")
	ESwipeType GetSwipeType();
	
	/** The number of fingers swiped */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gestures|Result")
	int32 TouchCount;
	
	UFUNCTION()
	void DelayHandleSwipe();
	
protected:
	// Overrides
	virtual void TouchEnded(int32 FingerIndex) override;
	virtual void ResetGesture() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	// Non UFUNCTION
	virtual ESwipeType SwipeDetectedWithFinger(int32 Index) const;
	
	/** Used to keep track of swipes with each finger */
	ESwipeType SwipeFound[EKeys::NUM_TOUCH_KEYS];
	
	
};
