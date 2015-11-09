// 2015  MartianCraft, LLC, See header file for license & copyright notice

#include "MobileGestureRecognizerPluginPrivatePCH.h"

UPanGestureRecognizer::UPanGestureRecognizer() 	: Super()
, MinimumTouchCount(1)
, MaximumTouchCount(10)
, bGestureBegan(false)
{
	
}

void UPanGestureRecognizer::DetectGestures(float DeltaTime)
{
	if (CurrentTouchCount >= MinimumTouchCount && CurrentTouchCount <= MaximumTouchCount)
	{
		if (!bGestureBegan)
		{
			bGestureBegan = true;
			GestureBeganDelegate.Broadcast(this, DeltaTime);
			
		}
		
		for (int32 Index = 0; Index < EKeys::NUM_TOUCH_KEYS; Index++)
		{
			if (Index < CurrentTouchCount)
			{
				TouchPoints[Index] = TouchData[Index].TouchPoints.Last();
			}
			else
			{
				TouchPoints[Index] = FVector2D(FLT_MAX, FLT_MAX);
			}
		}
		
		if (LastMoveDistanceInPointsForTouch(MinimumTouchCount - 1) != FVector2D::ZeroVector)
		{
			
			GestureMovedDelegate.Broadcast(this, DeltaTime);
			
		}
	}
}

void UPanGestureRecognizer::GestureFinished(float DeltaTime)
{
	if (bGestureBegan)
	{
		GestureEndedDelegate.Broadcast(this, DeltaTime);
	}
}

void UPanGestureRecognizer::ResetGesture()
{
	Super::ResetGesture();
	bGestureBegan = false;
}

int32 UPanGestureRecognizer::GetTouchCount()
{
	return CurrentTouchCount;
}

TArray<FVector2D> UPanGestureRecognizer::GetTouchPoints()
{
	TArray<FVector2D> Points;
	for (int32 Index = 0; Index < CurrentTouchCount; Index++)
	{
		Points.Add(TouchPoints[Index]);
	}
	return Points;
	
}

FVector2D UPanGestureRecognizer::FirstFingerTouchLocation()
{
	if (CurrentTouchCount > 0)
	{
		return TouchPoints[0];
	}
	return FVector2D::ZeroVector;
	
}

FVector2D UPanGestureRecognizer::LastMoveDistanceForFirstTouch()
{
	return LastMoveDistanceForTouch(0);
}

FVector2D UPanGestureRecognizer::LastMoveDistanceForFirstTouchInPoints()
{
	return UGestureMathLibrary::ScaleVector2DForScreen(LastMoveDistanceForTouch(0));
}

FVector2D UPanGestureRecognizer::LastMoveDistanceForTouch(int32 Touch)
{
	if (TouchData[Touch].TouchPoints.Num() <= 1)
		return FVector2D::ZeroVector;
	
	FVector2D LastTouchPoint = TouchData[Touch].TouchPoints.Last();
	FVector2D PreviousTouchPoint = TouchData[Touch].TouchPoints[TouchData[Touch].TouchPoints.Num() - 2];
	
	return LastTouchPoint - PreviousTouchPoint;
}

FVector2D UPanGestureRecognizer::LastMoveDistanceInPointsForTouch(int32 Touch)
{
	return UGestureMathLibrary::ScaleVector2DForScreen(LastMoveDistanceForTouch(Touch));
}