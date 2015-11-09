// 2015  MartianCraft, LLC, See header file for license & copyright notice


#include "OffscreenIndicatorPrivatePCH.h"

void UHUDBlueprintLibrary::FindScreenLocationForWorldLocation(UObject* WorldContextObject, const FVector& InLocation, const float EdgePercent,  FVector2D& OutScreenPosition, float& OutRotationAngleDegrees, bool &bIsOnScreen)
{
	bIsOnScreen = false;
	OutRotationAngleDegrees = 0.f;
	FVector2D *ScreenPosition = new FVector2D();
	
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (!World->IsValidLowLevel()) return;
	if (GEngine->GameViewport == NULL) return;
	if (GEngine->GameViewport->Viewport == NULL) return;
	
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D  ViewportCenter =  FVector2D(ViewportSize.X/2, ViewportSize.Y/2);
	


	APlayerController* PlayerController = (WorldContextObject ? UGameplayStatics::GetPlayerController(WorldContextObject, 0) : NULL);
	ACharacter *PlayerCharacter = static_cast<ACharacter *> (PlayerController->GetPawn());
	
	if (!PlayerCharacter) return;
	
	
	FVector Forward = PlayerCharacter->GetActorForwardVector();
	FVector Offset = (InLocation - PlayerCharacter->GetActorLocation()).GetSafeNormal();
	
	float DotProduct = FVector::DotProduct(Forward, Offset);
	bool bLocationIsBehindCamera = (DotProduct < 0);
	
	if (bLocationIsBehindCamera)
	{
		// For behind the camera situation, we cheat a little to put the
		// marker at the bottom of the screen so that it moves smoothly
		// as you turn around. Could stand some refinement, but results
		// are decent enough for most purposes.
		
		FVector DiffVector = InLocation - PlayerCharacter->GetActorLocation();
		FVector Inverted = DiffVector * -1.f;
		FVector NewInLocation = PlayerCharacter->GetActorLocation() * Inverted;
		
		NewInLocation.Z -= 5000;
		
		PlayerController->ProjectWorldLocationToScreen(NewInLocation, *ScreenPosition);
		ScreenPosition->Y = (EdgePercent * ViewportCenter.X) * 2.f;
		ScreenPosition->X = -ViewportCenter.X - ScreenPosition->X;
	}
	 
	PlayerController->ProjectWorldLocationToScreen(InLocation, *ScreenPosition);
	
	// Check to see if it's on screen. If it is, ProjectWorldLocationToScreen is all we need, return it.
	if (ScreenPosition->X >= 0.f && ScreenPosition->X <= ViewportSize.X
		&& ScreenPosition->Y >= 0.f && ScreenPosition->Y <= ViewportSize.Y)
	{
		OutScreenPosition = *ScreenPosition;
		bIsOnScreen = true;
		return;
	}
	
	*ScreenPosition -= ViewportCenter;

	float AngleRadians = FMath::Atan2(ScreenPosition->Y, ScreenPosition->X);
	AngleRadians -= FMath::DegreesToRadians(90.f);
	
	OutRotationAngleDegrees = FMath::RadiansToDegrees(AngleRadians) + 180.f;
	
	float Cos = cosf(AngleRadians);
	float Sin = -sinf(AngleRadians);
	
	ScreenPosition = new FVector2D(ViewportCenter.X + (Sin * 150.f), ViewportCenter.Y + Cos * 150.f);
	
	float m = Cos / Sin;
	
	FVector2D ScreenBounds = ViewportCenter * EdgePercent;
	
	if (Cos > 0)
	{
		ScreenPosition = new FVector2D(ScreenBounds.Y/m, ScreenBounds.Y);
	}
	else
	{
		ScreenPosition = new FVector2D(-ScreenBounds.Y/m, -ScreenBounds.Y);
	}
	
	if (ScreenPosition->X > ScreenBounds.X)
	{
		ScreenPosition = new FVector2D(ScreenBounds.X, ScreenBounds.X*m);
	}
	else if (ScreenPosition->X < -ScreenBounds.X)
	{
		ScreenPosition = new FVector2D(-ScreenBounds.X, -ScreenBounds.X*m);
	}
	
	*ScreenPosition += ViewportCenter;
	
	OutScreenPosition = *ScreenPosition;
	
}

bool UHUDBlueprintLibrary::IsPointOnScreenWithinDistance(UObject* WorldContextObject, const FVector& InWorldLocation, const float& InMaxDistance)
{
	float MaxDistanceSquared = InMaxDistance * InMaxDistance;
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	
	if (!World->IsValidLowLevel()) return false;
	
	APlayerController* PlayerController = (WorldContextObject ? UGameplayStatics::GetPlayerController(WorldContextObject, 0) : NULL);

	const FVector Forward = PlayerController->PlayerCameraManager->GetCameraRotation().Vector();
	//const FVector Forward = PlayerCharacter->GetActorForwardVector();
	const FVector CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
	const FVector Offset = (InWorldLocation - CameraLocation).GetSafeNormal();
	
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	
	float DotProduct = FVector::DotProduct(Forward, Offset);
	bool bLocationIsBehindCamera = (DotProduct < 0);
	
	if (bLocationIsBehindCamera)
	{
		return false;
	}
	
	FVector2D *ScreenPosition = new FVector2D();
	PlayerController->ProjectWorldLocationToScreen(InWorldLocation, *ScreenPosition);
	
	// Check to see if it's on screen. If it is, ProjectWorldLocationToScreen is all we need, return it.
	if (ScreenPosition->X >= 0.f && ScreenPosition->X <= ViewportSize.X
		&& ScreenPosition->Y >= 0.f && ScreenPosition->Y <= ViewportSize.Y)
	{
		FVector Delta = InWorldLocation - CameraLocation;
		float DistanceAwaySquared = Delta.SizeSquared();
		
		if (fabsf(DistanceAwaySquared) <= MaxDistanceSquared)
		{
			return true;
		}
	}
	
	return false;
}

FString UHUDBlueprintLibrary::GetCurrentLevelName(UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	FString MapName = World->GetMapName();
	FString MapPrefix = World->StreamingLevelsPrefix;
	MapName.ReplaceInline(*MapPrefix, TEXT(""));
	return MapName;
}

void UHUDBlueprintLibrary::Projected2DBoundsWithOriginAndExtent(UObject* WorldContextObject, FVector Origin, FVector Extents,FVector2D &OutCenter, FVector2D &OutSize)
{
	const FVector BoundsPointMapping[8] =
	{
		FVector(1.f,   1.f,  1.f),
		FVector(1.f,   1.f, -1.f),
		FVector(1.f,  -1.f,  1.f),
		FVector(1.f,  -1.f, -1.f),
		FVector(-1.f,  1.f,  1.f),
		FVector(-1.f,  1.f, -1.f),
		FVector(-1.f, -1.f,  1.f),
		FVector(-1.f, -1.f, -1.f)
	};
	
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	APlayerController *PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	if (!PlayerController || !PlayerController->IsValidLowLevelFast()) return;
	
	FBox ActorBox = FBox::BuildAABB(Origin, Extents);
	FVector ActorCenter = ActorBox.GetCenter();
	
	FVector2D ProjectedCenter;
	float MinX, MinY, MaxX, MaxY;
	PlayerController->ProjectWorldLocationToScreen(ActorCenter, ProjectedCenter);
	MinX = MaxX = ProjectedCenter.X;
	MinY = MaxY = ProjectedCenter.Y;
	
	//FBox2D ActorBox2D(0);
	for (uint8 BoundsPointItr = 0; BoundsPointItr < 8; BoundsPointItr++)
	{
		// Project vert into screen space.
		FVector Corner = ActorCenter + (BoundsPointMapping[BoundsPointItr] * Extents);
		FVector2D ProjectedCorner;
		PlayerController->ProjectWorldLocationToScreen(Corner, ProjectedCorner);
		if (MinX > ProjectedCorner.X) MinX = ProjectedCorner.X;
		if (MaxX < ProjectedCorner.X) MaxX = ProjectedCorner.X;
		if (MinY > ProjectedCorner.Y) MinY = ProjectedCorner.Y;
		if (MaxY < ProjectedCorner.Y) MaxY = ProjectedCorner.Y;
		//ActorBox2D += ProjectedWorldLocation;
	}
	OutCenter.X = MinX + ((MaxX - MinX) / 2.f);
	OutCenter.Y = MinY + ((MaxY - MinY) / 2.f);
	OutSize.X = fabsf(MaxX - MinX);
	OutSize.Y = fabsf(MaxY - MinY);
}

void UHUDBlueprintLibrary::Projected2DBoundsBoxForBoxComponent(UObject* WorldContextObject, const UBoxComponent *Component, FVector2D &OutCenter, FVector2D &OutSize)
{
	const FVector BoundsPointMapping[8] =
	{
		FVector(1.f,   1.f,  1.f),
		FVector(1.f,   1.f, -1.f),
		FVector(1.f,  -1.f,  1.f),
		FVector(1.f,  -1.f, -1.f),
		FVector(-1.f,  1.f,  1.f),
		FVector(-1.f,  1.f, -1.f),
		FVector(-1.f, -1.f,  1.f),
		FVector(-1.f, -1.f, -1.f)
	};
	
	FVector ActorOrigin = Component->GetComponentLocation();
	FVector ActorExtents = Component->GetScaledBoxExtent();
	
	Projected2DBoundsWithOriginAndExtent(WorldContextObject, ActorOrigin, ActorExtents, OutCenter, OutSize);
}

void UHUDBlueprintLibrary::Projected2DBoundsBoxForActor(UObject* WorldContextObject, const AActor *Actor, FVector2D &OutCenter, FVector2D &OutSize)
{
	const FVector BoundsPointMapping[8] =
	{
		FVector(1.f,   1.f,  1.f),
		FVector(1.f,   1.f, -1.f),
		FVector(1.f,  -1.f,  1.f),
		FVector(1.f,  -1.f, -1.f),
		FVector(-1.f,  1.f,  1.f),
		FVector(-1.f,  1.f, -1.f),
		FVector(-1.f, -1.f,  1.f),
		FVector(-1.f, -1.f, -1.f)
	};
	
	FVector ActorOrigin, ActorExtents;
	
	
	Actor->GetActorBounds(true, ActorOrigin, ActorExtents);
	
	Projected2DBoundsWithOriginAndExtent(WorldContextObject, ActorOrigin, ActorExtents, OutCenter, OutSize);
}