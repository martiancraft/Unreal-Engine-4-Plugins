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
#include "GestureMathLibrary.h"
#include "GestureRecognizerComponent.generated.h"


USTRUCT()
struct FGestureTouchData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	TArray<FVector2D> TouchPoints;
	
	UPROPERTY()
	TArray<float> TouchStartTimes;
	
	UPROPERTY()
	TArray<float> TouchEndTimes;
	
	// The time of the first detected touch of this gesture
	UPROPERTY()
	float FirstTouchTime;
	
	// The time of the most recent detected touch of this gesture
	UPROPERTY()
	float LatestTouchTime;
	
	// Returns true if the finger associated with this touch has lifted from the screen
	UPROPERTY()
	bool bIsTouchEnded;
	
	UPROPERTY()
	bool bIsTouchStarted;
	
	/** Straight line distance in pixels from start to end of this gesture */
	float GestureLength()
	{
		FVector2D StartPosition = TouchPoints[0];
		FVector2D EndPosition = TouchPoints.Last();
		
		float Distance = (EndPosition - StartPosition).Size();
		return Distance;
	};
	
	/** Straight line distance in points from start to end of this gesture */
	float GestureLengthInPoints()
	{
		return UGestureMathLibrary::ScaleFloatForScreen(GestureLength());
	};
	
	/** The amount of time between when this touch started and when it ended, if it ended, or between the start time and now otherwise */
	float ElapsedTime()
	{
		return LatestTouchTime - FirstTouchTime;
	};
	
	/** Actual length of the gesture path in device pixels */
	float PixelsTraveled()
	{
		float DistanceTraveled = 0.f;
		
		for (int32 Index = 0; Index < TouchPoints.Num() - 1; Index++)
		{
			FVector2D CurrentPoint = TouchPoints[Index];
			FVector2D NextPoint = TouchPoints[Index+1];
			DistanceTraveled += (NextPoint - CurrentPoint).Size();
		}
		return DistanceTraveled;
	}
	
	/** Length of the gesture path normalized for the density of the screen */
	float PointsTraveled()
	{
		return UGestureMathLibrary::ScaleFloatForScreen(PixelsTraveled());
	}
	
	/** Straight-line distance on the X-axis for this touch, in device pixels, negative numbers indicate left movement, positive right*/
	float XDifference()
	{
		FVector2D StartPosition = TouchPoints[0];
		FVector2D EndPosition = TouchPoints.Last();
		
		return EndPosition.X - StartPosition.X;
	}
	
	/** Straight-line distance on the X-axis for this touch, normalized for the density of the screen, negative numbers indicate left movement, positive right */
	float XDifferenceInPoints()
	{
		return UGestureMathLibrary::ScaleFloatForScreen(XDifference());
	}
	
	/** How many device pixels traveled along the X-axis (absolute value of XDifference). Always positive, does not indicate direction of travel */
	float XDistance()
	{
		return fabsf(XDifference());
	}
	
	/** How many points (pixels normalized by screen resolution) traveled along the X-axis (absolute value of XDifference). Always positive, does not indicate direction of travel */
	float XDistanceInPoints()
	{
		return UGestureMathLibrary::ScaleFloatForScreen(XDistance());
	}
	
	/** Straight-line distance on the Y-axis for this touch, in device pixels, negative numbers indicate left movement, positive right*/
	float YDifference()
	{
		FVector2D StartPosition = TouchPoints[0];
		FVector2D EndPosition = TouchPoints.Last();
		
		return EndPosition.Y - StartPosition.Y;
	}
	
	/** Straight-line distance on the Y-axis for this touch, normalized for the density of the screen, negative numbers indicate left movement, positive right */
	float YDifferenceInPoints()
	{
		return UGestureMathLibrary::ScaleFloatForScreen(YDifference());
	}
	
	/** How many device pixels traveled along the Y-axis (absolute value of XDifference). Always positive, does not indicate direction of travel */
	float YDistance()
	{
		return fabsf(YDifference());
	}
	
	/** How many points (pixels normalized by screen resolution) traveled along the Y-axis (absolute value of XDifference). Always positive, does not indicate direction of travel */
	float YDistanceInPoints()
	{
		return UGestureMathLibrary::ScaleFloatForScreen(YDistance());
	}
	
	bool IsOnLeftHalfOfScreen()
	{
		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		const FVector2D ViewportCenter =  FVector2D(ViewportSize.X/2, ViewportSize.Y/2);
		
		FVector2D Point = TouchPoints.Last();
		return (Point.X <= ViewportCenter.X);
	}
	
	bool IsOnRightHalfOfScreen()
	{
		return !IsOnRightHalfOfScreen();
	}
};
class UGestureRecognizerComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGestureEnded, UGestureRecognizerComponent *, Recognizer, float, DeltaTime);

/** Base class for gesture recognizer components. This class doesn't recognize any gestures, it simply provides a base class that concrete gesture recognizers can use */

UCLASS(ClassGroup=Input, meta=(BlueprintSpawnableComponent))
class UGestureRecognizerComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	/** If touch data should be flushed when the last finger is removed from the screen. Subclasses that change this to `false` are responsible for manually flushing touch data when appropriate */
	UPROPERTY()
	bool bFlushTouchDataOnGestureEnded;
	
	/** If touch data is flushed, this is an optional delay before flushing */
	UPROPERTY()
	float DelayBeforeResetting;
	
	UGestureRecognizerComponent();
	virtual void InitializeComponent() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	// ===========================================================================
	// Delegates
	
	/** Delegate function called when a gesture is completed. For simple gestures, like swipes and taps, this is the only delegate function that will get called. For ongoing gestures, this will indicate that the gesture has ended and no more FGestureMoved calls will happen until the next gesture starts.
	 */
	UPROPERTY(BlueprintAssignable, Category=Gestures)
	FGestureEnded GestureEndedDelegate;
	
	
	// ===========================================================================
	// Gesture detection
	
	UFUNCTION(BlueprintCallable, Category="Gestures|Detection")
	/** Subclasses should override this to detect gestures that require tick-level precision **/
	virtual void DetectGestures(float DeltaTime);
	
	/** Called when the last finger of a gesture is lifted off of the screen. Good class to override for simle gesture detection */
	virtual void GestureFinished(float DeltaTime);
	
	/** Called when a finger touches down for the first time during a gesture */
	virtual void TouchBegan(int32 FingerIndex, FVector2D Position);
	
	/** Called while a finger is touching the screen */
	virtual void TouchMoved(int32 FingerIndex, FVector2D Position);
	
	/** Called when a finger is lifted from the screen */
	virtual void TouchEnded(int32 FingerIndex);
	
	// ===========================================================================
	int32 FORCEINLINE GetCurrentTouchCount() {return CurrentTouchCount;};
	int32 FORCEINLINE GetPreviousTouchCount() {return PreviousTouchCount;};
	int32 FORCEINLINE GetMaxFingersThisGesture() {return MaxFingersThisGesture;};
	
protected:
	
	// This stores information about each of the possible touches.
	FGestureTouchData TouchData[EKeys::NUM_TOUCH_KEYS];
	int32 CurrentTouchCount;
	int32 PreviousTouchCount;
	UPlayerInput *PlayerInput;
	int32 MaxFingersThisGesture;
	float FirstFingerTouchTime;
	float LastFingerTouchTime;
	
	virtual void ResetGesture(void);
	
private:
	void CalculateTouchCount(const FVector (&Touches)[EKeys::NUM_TOUCH_KEYS]);
	void UpdateStoredTouchData(const FVector (&Touches)[EKeys::NUM_TOUCH_KEYS]);
	void ProcessTouches(const FVector (&Touches)[EKeys::NUM_TOUCH_KEYS], float DeltaTime);
	
	bool bWasDownPreviously[EKeys::NUM_TOUCH_KEYS];
};
