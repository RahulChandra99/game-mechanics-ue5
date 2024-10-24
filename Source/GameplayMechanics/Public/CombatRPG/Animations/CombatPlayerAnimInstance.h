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
	float CurrentSpeed {0.0f};

	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInCombat { false };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentDirection { 0.0f };

public:
	UFUNCTION(BlueprintCallable)
	void HandleUpdatedTarget(AActor* NewTargetActor);
	
	UFUNCTION(BlueprintCallable)
	void UpdateDirection();
};
