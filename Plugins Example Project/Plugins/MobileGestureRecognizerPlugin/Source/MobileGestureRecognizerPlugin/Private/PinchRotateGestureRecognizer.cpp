// 2015  MartianCraft, LLC, See header file for license & copyright notice

#include "MobileGestureRecognizerPluginPrivatePCH.h"

UPinchRotateGestureRecognizer::UPinchRotateGestureRecognizer() : Super ()
, MinimumAngleChangeForRotate(1.f)
, MinimumDistanceChangeForPinch(2.f)
, DeltaRotationDegrees(0.f)
, AccumulatedAngleChange(0.f)
, DeltaDistancePixels(0.f)
, AccumulatedDistanceChange(0.f)
, bIsPinching(false)
, bIsRotating(false)
{
	
}

void UPinchRotateGestureRecognizer::DetectGestures(float DeltaTime)
{
	// If finger is lifted up, or an additional finger added,
	// treat the gesture as over.
	if (CurrentTouchCount != 2)
	{
		if (bIsRotating || bIsPinching)
		{
			GestureEndedDelegate.Broadcast(this, DeltaTime);
		}
		ResetGesture();
		AccumulatedAngleChange = 0.f;
		return;
	}
	
	// If we don't have two points yet, there's nothing to compare
	if (TouchData[0].TouchPoints.Num() <= 1)
	{
		return;
	}
	
	FVector2D Touch1Start = TouchData[0].TouchPoints[TouchData[0].TouchPoints.Num() - 2];
	FVector2D Touch1End = TouchData[0].TouchPoints[TouchData[0].TouchPoints.Num() - 1];

	FVector2D Touch2Start = TouchData[1].TouchPoints[TouchData[1].TouchPoints.Num() - 2];
	FVector2D Touch2End = TouchData[1].TouchPoints[TouchData[1].TouchPoints.Num() - 1];
	
	
	// @TODO: This isn't working right
	DeltaRotationDegrees = UGestureMathLibrary::AngleBetweenLines(Touch1Start, Touch1End, Touch2Start, Touch2End);
	AccumulatedAngleChange = AccumulatedAngleChange + DeltaRotationDegrees;
	
	if (fabsf(AccumulatedAngleChange) > MinimumAngleChangeForRotate)
	{
		bIsRotating = true;
	}
	
	
	float PreviousDistance = (Touch1End - Touch1Start).Size();
	float CurrentDistance = (Touch2End - Touch2Start).Size();
	
	DeltaDistancePixels = CurrentDistance - PreviousDistance;
	DeltaDistancePixels = UGestureMathLibrary::ScaleFloatForScreen(DeltaDistancePixels);
	
	AccumulatedDistanceChange += DeltaDistancePixels;
	
	if (fabsf(AccumulatedDistanceChange) > MinimumDistanceChangeForPinch)
	{
		bIsPinching = true;
	}
	
	if (bIsPinching || bIsRotating)
	{
		GestureMovedDelegate.Broadcast(this, DeltaTime);
	}
	
}

void UPinchRotateGestureRecognizer::GestureFinished(float DeltaTime)
{
	if (bIsPinching || bIsRotating)
	{
		GestureEndedDelegate.Broadcast(this, DeltaTime);
	}
}

void UPinchRotateGestureRecognizer::ResetGesture()
{
	Super::ResetGesture();
	AccumulatedAngleChange = 0.f;
	AccumulatedDistanceChange = 0.f;
	bIsPinching = false;
	bIsRotating = false;
}