// 2015  MartianCraft, LLC, See header file for license & copyright notice

#include "MobileGestureRecognizerPluginPrivatePCH.h"

UTapGestureRecognizer::UTapGestureRecognizer() 	: Super()
, MinimumTimeForTap(0.f)
, MaximumTimeForTap(0.3f)
, MinimumTouchCount(1)
, MaximumTouchCount(1)
, MinimumNumberOfTaps(1)
, MaximumNumberOfTaps(MAX_int32)
, Tolerance(15)
, MaximumTimeBetweenTaps(.25f)
, NumberOfFingersInTap(0)

{
	bFlushTouchDataOnGestureEnded = false;
}


FVector2D UTapGestureRecognizer::GetTapLocation() const
{
	return LastTapLocation;
}

bool UTapGestureRecognizer::TapWasOnLeftHalf()
{
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D ViewportCenter =  FVector2D(ViewportSize.X/2, ViewportSize.Y/2);
	const FVector2D LastTouch = GetTapLocation();
	
	return LastTouch.X <= ViewportCenter.X;
}

bool UTapGestureRecognizer::TapWasOnRightHalf()
{
	return !TapWasOnLeftHalf();
}

bool UTapGestureRecognizer::TapWasOnTopHalf()
{
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D ViewportCenter =  FVector2D(ViewportSize.X/2, ViewportSize.Y/2);
	const FVector2D LastTouch = GetTapLocation();
	
	return LastTouch.Y <= ViewportCenter.Y;
}

bool UTapGestureRecognizer::TapWasOnBottomHalf()
{
	return !TapWasOnTopHalf();
}
void UTapGestureRecognizer::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentTouchCount > PreviousTouchCount) // more fingers this tick than last means a tap sequence can't have ended
	{
		return;
	}
	
	float Now = GetWorld()->GetRealTimeSeconds();
	
	for (int32 i = 0; i < EKeys::NUM_TOUCH_KEYS; i++)
	{
		TapCounts[i] = 0;
	}
	
	bool bDidFindTapSequence = false;
	// If less fingers on screen, we could have a tap sequence in any of the fingers
	for (int32 Index = CurrentTouchCount; Index < EKeys::NUM_TOUCH_KEYS; Index++)
	{
		FGestureTouchData ThisTouch = TouchData[Index];
		if (ThisTouch.TouchStartTimes.Num() == 0) continue; // No points to look at, so bail
		
		if (Now > ThisTouch.LatestTouchTime + MaximumTimeBetweenTaps && ThisTouch.LatestTouchTime != 0.f)
		{
			// Make sure it wasn't a pan or swipe
			if (ThisTouch.TouchPoints.Num() > 1)
			{
				FVector2D TouchDelta = ThisTouch.TouchPoints.Last() - ThisTouch.TouchPoints[0];
				TouchDelta = UGestureMathLibrary::ScaleVector2DForScreen(TouchDelta);
				float MovementSquared = TouchDelta.SizeSquared();
				if (MovementSquared > ToleranceSquared) //
				{
					// Not a tap, move along
					ResetGesture();
					continue;
				}
			}
			
			// Enough time has passed that this finger MIGHT have finished a tap sequence
			for (int32 TouchTimeIndex = ThisTouch.TouchStartTimes.Num()-1; TouchTimeIndex >= 0; TouchTimeIndex--)
			{
				float TapDuration = ThisTouch.TouchEndTimes[TouchTimeIndex] - ThisTouch.TouchStartTimes[TouchTimeIndex];
				if ( TapDuration >= MinimumTimeForTap && TapDuration <= MaximumTimeForTap)
				{
					// We have a tap! But was it part of a sequence?
					
					// First valid touch doesn't need this check
					if (TouchTimeIndex == ThisTouch.TouchStartTimes.Num()-1)
					{
						TapCounts[Index]++;
					}
					// Need to include 0 in the loop for single taps, but don't want to try and compare it with previous tap
					if (TouchTimeIndex > 0)
					{
						if (ThisTouch.TouchStartTimes[TouchTimeIndex] <= ThisTouch.TouchStartTimes[TouchTimeIndex-1] + MaximumTimeBetweenTaps)
						{
							TapCounts[Index]++;
						}
					}
				}
				else
				{
					break; // Not fast enough for tap
				}
			}
		}
		
		// Don't want to count this one again!
		if (TapCounts[Index] > 0)
		{
			bDidFindTapSequence = true;
		}
	}
	if (bDidFindTapSequence)
	{
		NumberOfFingersInTap = 0;
		int32 HighestTapCount = 0;
		int32 FirstIndexMatchingHighestTapCount;
		
		// Find the highest tap count for a finger
		for (int32 Index = 0; Index < EKeys::NUM_TOUCH_KEYS; Index++)
		{
			if (TapCounts[Index] > HighestTapCount)
			{
				HighestTapCount = TapCounts[Index];
				FirstIndexMatchingHighestTapCount = Index;
			}
		}
		// Find out how many fingers tapped for that amount
		for (int32 Index = 0; Index < EKeys::NUM_TOUCH_KEYS; Index++)
		{
			if (TapCounts[Index] == HighestTapCount)
			{
				NumberOfFingersInTap++;
			}
		}
		NumberOfTaps = HighestTapCount;
		LastTapLocation = TouchData[FirstIndexMatchingHighestTapCount].TouchPoints.Last();
		
		if (NumberOfTaps >= MinimumNumberOfTaps &&
			NumberOfTaps <= MaximumNumberOfTaps &&
			NumberOfFingersInTap >= MinimumTouchCount &&
			NumberOfFingersInTap <= MaximumTouchCount)
		{
			GestureEndedDelegate.Broadcast(this, DeltaTime);
		}
		ResetGesture();
	}
	
}
void UTapGestureRecognizer::InitializeComponent()
{
	Super::InitializeComponent();
	ToleranceSquared = Tolerance * Tolerance;
	
}