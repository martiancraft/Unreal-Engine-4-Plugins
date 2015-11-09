// 2015  MartianCraft, LLC, See header file for license & copyright notice

#include "MobileGestureRecognizerPluginPrivatePCH.h"

void UInstantTapRecognizer::TouchBegan(int32 FingerIndex, FVector2D Position)
{
	WhichFinger = FingerIndex;
	TouchLocation = Position;
	GestureBeganDelegate.Broadcast(this, GetWorld()->GetDeltaSeconds());
}

void UInstantTapRecognizer::TouchEnded(int32 FingerIndex)
{
	WhichFinger = FingerIndex;
	TouchLocation = TouchData[FingerIndex].TouchPoints.Last();
	GestureEndedDelegate.Broadcast(this, GetWorld()->GetDeltaSeconds());
}