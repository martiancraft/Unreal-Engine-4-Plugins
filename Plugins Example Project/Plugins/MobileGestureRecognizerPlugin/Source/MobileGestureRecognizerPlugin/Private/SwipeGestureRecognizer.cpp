// ©2015 MartianCraft, LLC, See header file for license & copyright notice

#include "MobileGestureRecognizerPluginPrivatePCH.h"

USwipeGestureRecognizer::USwipeGestureRecognizer() 	: Super()
{
	MinimumSwipeDistance = 50.f;
	Tolerance = 40.f;
	MaximumGestureDuration = .5f;
	MaximumTouches = 1;
	MinimumTouches = 1;
	bFlushTouchDataOnGestureEnded = false;
}
void USwipeGestureRecognizer::ResetGesture()
{
	Super::ResetGesture();
	
	TouchCount = 0;
	for (int32 Index = 0; Index < ARRAY_COUNT(SwipeFound); Index++)
	{
		SwipeFound[Index] = ESwipeType::SwipeNone;
	}
}
void USwipeGestureRecognizer::TouchEnded(int32 FingerIndex)
{
	SwipeFound[FingerIndex] = SwipeDetectedWithFinger(FingerIndex);
}
ESwipeType USwipeGestureRecognizer::SwipeDetectedWithFinger(int32 Index) const
{
	FGestureTouchData ThisTouch = TouchData[Index];
	
	if (ThisTouch.GestureLengthInPoints() < MinimumSwipeDistance)
	{
		return ESwipeType::SwipeNone;
	}
	
	if (ThisTouch.ElapsedTime() > MaximumGestureDuration)
	{
		return ESwipeType::SwipeNone;
	}
	
	FVector2D StartPoint = ThisTouch.TouchPoints[0];
	FVector2D EndPoint = ThisTouch.TouchPoints.Last();
	float XDistance = ThisTouch.XDistanceInPoints();
	float YDistance = ThisTouch.YDistanceInPoints();
	float YDifference = ThisTouch.YDifferenceInPoints();
	float XDifference = ThisTouch.XDifferenceInPoints();
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	
	float HorizontalEdgeTolerance = .1f * ViewportSize.X;
	float VerticalEdgeTolerance = .1f * ViewportSize.Y;
	
	// Horizontal Swipes
	if (XDistance >= MinimumSwipeDistance && YDistance < Tolerance)
	{
		// @TODO: Swipe from edges need a tolerance value, probably based on percentage of screen size.
		// Swipe from Left Edge
		if (StartPoint.X <= HorizontalEdgeTolerance && XDifference > 0.f)
		{
			if (SupportedSwipes.bSupportsSwipeFromLeftEdge)
			{
				return ESwipeType::SwipeFromLeftEdge;
			}
		}
		// Swipe Right
		else if (XDifference > 0.f)
		{
			if (SupportedSwipes.bSupportsSwipeRight)
			{
				return ESwipeType::SwipeRight;
			}
		}
		// Swipe from Right Edge
		else if (StartPoint.X >= (ViewportSize.X - HorizontalEdgeTolerance))
		{
			if (SupportedSwipes.bSupportsSwipeFromRightEdge)
			{
				return ESwipeType::SwipeFromRightEdge;
			}
		}
		// Swipe Left
		else
		{
			if (SupportedSwipes.bSupportsSwipeLeft)
			{
				return ESwipeType::SwipeLeft;
			}
		}
	}
	// Vertical Swipes
	else if (YDistance >= MinimumSwipeDistance && XDistance < Tolerance)
	{
		// Swipe from Top Edge
		if (StartPoint.Y <= VerticalEdgeTolerance && YDifference > 0.f)
		{
			if (SupportedSwipes.bSupportsSwipeFromTopEdge)
			{
				return ESwipeType::SwipeFromTopEdge;
			}
		}
		// Swipe Up
		else if (YDifference > 0.f)
		{
			if (SupportedSwipes.bSupportsSwipeUp)
			{
				return ESwipeType::SwipeDown;
			}
		}
		// Swipe from Bottom
		else if (StartPoint.Y > (ViewportSize.Y - VerticalEdgeTolerance))
		{
			if (SupportedSwipes.bSupportsSwipeFromBottomEdge)
			{
				return ESwipeType::SwipeFromBottomEdge;
			}
		}
		// Swipe Up
		else
		{
			if (SupportedSwipes.bSupportsSwipeDown)
			{
				return ESwipeType::SwipeUp;
			}
		}
	}
	// Diagonal Swipes
	else if (YDistance >= MinimumSwipeDistance && XDistance >= MinimumSwipeDistance)
	{
		// Up and Right
		if (YDifference < 0.f && XDifference > 0.f)
		{
			if (SupportedSwipes.bSupportsSwipeDiagonalUpRight)
			{
				return ESwipeType::SwipeUpRight;
			}
		}
		// Up and Left
		else if (YDifference < 0.f && XDifference < 0.f)
		{
			if (SupportedSwipes.bSupportsSwipeDiagonalUpLeft)
			{
				return ESwipeType::SwipeUpLeft;
			}
		}
		// Down and Right
		else if (YDifference > 0.f && XDifference > 0.f)
		{
			if (SupportedSwipes.bSupportsSwipeDiagonalDownRight)
			{
				return ESwipeType::SwipeDownRight;
			}
		}
		// Down and Left
		else
		{
			if (SupportedSwipes.bSupportsSwipeDiagonalDownLeft)
			{
				return ESwipeType::SwipeDownLeft;
			}
		}
	}
	
	
	return ESwipeType::SwipeNone;
}

ESwipeType USwipeGestureRecognizer::GetSwipeType()
{
	return SwipeType;
}

void USwipeGestureRecognizer::DelayHandleSwipe()
{
	int32 FingerCount = 0;
	
	for (int32 Index = 0; Index < ARRAY_COUNT(SwipeFound); Index++)
	{
		if (SwipeFound[Index] == SwipeType)
		{
			FingerCount++;
		}
	}
	
	if (FingerCount >= MinimumTouches && FingerCount <= MaximumTouches)
	{
		TouchCount = FingerCount;
		GestureEndedDelegate.Broadcast(this, GetWorld()->GetDeltaSeconds());
	}
	
	if (DelayBeforeResetting == 0.f)
	{
		ResetGesture();
	}
	else
	{
		FTimerHandle Handle;
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &USwipeGestureRecognizer::ResetGesture, DelayBeforeResetting, false);
	}
	
}

void USwipeGestureRecognizer::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ESwipeType FoundSwipe = ESwipeType::SwipeNone;
	
	// Look for the first swipe of any type
	for (int32 Index = 0; Index < ARRAY_COUNT(SwipeFound); Index++)
	{
		if (SwipeFound[Index] != ESwipeType::SwipeNone)
		{
			FoundSwipe = SwipeFound[Index];
			break;
		}
	}
	
	// Did we find at least one swipe? If not, bail
	if (FoundSwipe == ESwipeType::SwipeNone)
	{
		return;
	}
	SwipeType = FoundSwipe;
	
	
	// At least one swipe, give a tiny bit of time for other fingers to leave glass for multi-finger swipes and then notify delegate
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &USwipeGestureRecognizer::DelayHandleSwipe, .1f, false);
	
}
