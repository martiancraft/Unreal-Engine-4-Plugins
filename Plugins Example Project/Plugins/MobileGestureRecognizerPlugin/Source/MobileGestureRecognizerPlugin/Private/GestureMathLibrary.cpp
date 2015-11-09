// 2015  MartianCraft, LLC, See header file for license & copyright notice

#include "MobileGestureRecognizerPluginPrivatePCH.h"

float UGestureMathLibrary::AngleBetweenLines(const FVector2D& Line1Start, const FVector2D& Line1End, const FVector2D& Line2Start, const FVector2D& Line2End)
{
	float A = Line1End.X - Line1Start.X;
	float B = Line1End.Y - Line1Start.Y;
	float C = Line2End.X - Line2Start.X;
	float D = Line2End.Y - Line2Start.Y;
	
	float Line1Slope = ((Line1End.X - Line1Start.X) == 0.f) ? 0.f : (Line1End.Y - Line1Start.Y) / (Line1End.X - Line1Start.X);
	float Line2Slope = ((Line2End.X - Line2Start.X) == 0.f) ? 0.f : (Line2End.Y - Line2Start.Y) / (Line2End.X - Line2Start.X);
	
	float Angle = acosf(((A * C) + (B * D)) / ((sqrtf(A * A + B * B)) * (sqrtf(C * C + D * D))));
	
	if (Angle == 0.f) return 0.f;
	
	if (isnan(Angle) || isnan(-Angle))
		return 0.f;
	
	
	return (Line2Slope > Line1Slope) ? Angle : -Angle;
	
}
bool UGestureMathLibrary::PointOnLeftHalfOfScreen(FVector2D Point)
{
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D ViewportCenter =  FVector2D(ViewportSize.X/2, ViewportSize.Y/2);
	
	return (Point.X <= ViewportCenter.X);
}

bool UGestureMathLibrary::PointOnRightHalfOfScreen(FVector2D Point)
{
	return !PointOnLeftHalfOfScreen(Point);
}

bool UGestureMathLibrary::PointOnTopHalfOfScreen(FVector2D Point)
{
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D ViewportCenter =  FVector2D(ViewportSize.X/2, ViewportSize.Y/2);
	
	return (Point.Y <= ViewportCenter.Y);
}

bool UGestureMathLibrary::PointOnBottomHalfOfScreen(FVector2D Point)
{
	return !(PointOnTopHalfOfScreen(Point));
}

float UGestureMathLibrary::GetScalingFactorForScreen()
{
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const float ViewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(ViewportSize.X, ViewportSize.Y));
	
	return ViewportScale;
}

float UGestureMathLibrary::ScaleFloatForScreen(float Value)
{
	return Value * GetScalingFactorForScreen();
}

FVector2D UGestureMathLibrary::ScaleVector2DForScreen(FVector2D Value)
{
	return Value * GetScalingFactorForScreen();
}