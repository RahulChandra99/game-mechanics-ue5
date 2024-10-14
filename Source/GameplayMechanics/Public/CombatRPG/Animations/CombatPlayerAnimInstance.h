// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CombatPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYMECHANICS_API UCombatPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentVelocity {0.0f};

	UFUNCTION(BlueprintCallable)
	void SetCurrentVelocity();
};
