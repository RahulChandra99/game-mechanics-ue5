// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"

class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYMECHANICS_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	USkeletalMeshComponent* SkeletalComp;

	UPROPERTY(EditAnywhere)
	FName Start;

	UPROPERTY(EditAnywhere)
	FName End;

	UPROPERTY(EditAnywhere)
	FName Rotation;

	UPROPERTY(EditAnywhere)
	double BoxCollisionLength { 30.f };

	UPROPERTY(EditAnywhere)
	bool bDebugMode { false };

	
	
public:	
	// Sets default values for this component's properties
	UTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
