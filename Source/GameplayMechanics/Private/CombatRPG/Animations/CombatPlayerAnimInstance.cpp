// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatRPG/Animations/CombatPlayerAnimInstance.h"

void UCombatPlayerAnimInstance::SetCurrentVelocity()
{
	APawn* PawnRef { TryGetPawnOwner() };

	if(!IsValid(PawnRef)) { return; }

	FVector Velocity { PawnRef->GetVelocity() };

	CurrentVelocity = static_cast<float>(Velocity.Length());
}
