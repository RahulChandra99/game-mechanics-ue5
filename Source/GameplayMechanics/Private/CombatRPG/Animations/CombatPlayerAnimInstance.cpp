// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatRPG/Animations/CombatPlayerAnimInstance.h"

void UCombatPlayerAnimInstance::UpdateSpeed()
{
	APawn* PawnRef { TryGetPawnOwner() };

	if(!IsValid(PawnRef)) { return; }

	FVector Velocity { PawnRef->GetVelocity() };

	CurrentSpeed = static_cast<float>(Velocity.Length());
}

void UCombatPlayerAnimInstance::HandleUpdatedTarget(AActor* NewTargetActoRefr)
{
	bIsInCombat = IsValid(NewTargetActoRefr);
	
}

void UCombatPlayerAnimInstance::UpdateDirection()
{
	APawn* PawnRef{ TryGetPawnOwner() };

	if(!IsValid(PawnRef)) { return;}

	if (!bIsInCombat) { return; }

	CurrentDirection = CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation()
	);
}

