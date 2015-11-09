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

#include "LookAtMovementComponent.generated.h"

/**
 * This component will cause an actor to keep itself oriented toward the local player or another actor or point in the world. Collision is disabled during movement.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOOKATCOMPONENTPLUGIN_API ULookAtMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
public:
	ULookAtMovementComponent();
	
	/** If `true`, the object will orient itself toward the local player. If false, then it will look at `ActorToLookAt` if not NULL, otherwise, it will use `LocationToLookAt`. If none of these are provided, it will look at the world origin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Look At Component")
	bool LookAtLocalPlayer;
	
	/** If `LookAtLocalPlayer` is `false`, then the actor this component is attached to will orient itself towards this actor, if one is specified */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Look At Component",  meta=(EditCondition="!LookAtLocalPlayer"))
	AActor *ActorToLookAt;
	
	/** If 'LookAtLocalPlayer` is `false` and `ActorToLookAt` is `NULL`, then the object this component is attached to will orient itself towards this world location. Defaults to world origin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Look At Component",  meta=(EditCondition="!LookAtLocalPlayer"))
	FVector LocationToLookAt;
	
	/** An optional offset value. If a value other than `ZeroRotator` is specified, this rotation will be applied after the look at rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Look At Component")
	FRotator Offset;
	
	/** Speed that it rotates */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Look At Component")
	float AimSpeed;
	
	/** If `true`, prevents pitch rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Look At Component")
	bool bLockPitch;
	
	/** If `true`, prevents yaw */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Look At Component")
	bool bLockYaw;
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
