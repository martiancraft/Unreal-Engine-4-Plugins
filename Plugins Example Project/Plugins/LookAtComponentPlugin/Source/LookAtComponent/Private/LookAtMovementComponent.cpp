// 2015  MartianCraft, LLC, See header file for license & copyright notice

#include "LookAtComponentPluginPrivatePCH.h"

ULookAtMovementComponent::ULookAtMovementComponent()
{
	LookAtLocalPlayer = true;
	LocationToLookAt = FVector::ZeroVector;
	Offset = FRotator::ZeroRotator;
	AimSpeed = 2.f;
}

void ULookAtMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector Destination = FVector::ZeroVector;
	
	if (LookAtLocalPlayer)
	{
		ACharacter *Player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Player && Player->IsValidLowLevelFast())
		{
			Destination = Player->GetActorLocation();
		}
	}
	else if (ActorToLookAt && ActorToLookAt->IsValidLowLevel())
	{
		Destination = ActorToLookAt->GetActorLocation();
	}
	else
	{
		Destination = LocationToLookAt;
	}
	
	FVector DeltaVector = Destination - GetOwner()->GetActorLocation();
	
	FRotator FinalDestination = FRotationMatrix::MakeFromX(DeltaVector).Rotator() + Offset;
	
	FRotator Rot = FMath::RInterpTo(GetOwner()->GetActorRotation(), FinalDestination, DeltaTime, AimSpeed);
	
	FVector DeltaLocation = FVector::ZeroVector;
	const bool bEnableCollision = false;
	
	if (bLockPitch)
	{
		Rot.Pitch = 0.f;
	}
	
	if (bLockYaw)
	{
		Rot.Yaw = 0.f;
	}
	
	MoveUpdatedComponent(DeltaLocation, Rot, bEnableCollision);

}