// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatRPG/Combat/LockOnComponent.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void ULockOnComponent::StartLockOn(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation{ GetOwner()->GetActorLocation() };
	FCollisionShape Sphere { FCollisionShape::MakeSphere(Radius)};
	FCollisionQueryParams IgnoreParams{
		FName { TEXT("Ignore Collision Params")},
		false,
		GetOwner()
	};
	
	
	bool bHasFoundTarget { GetWorld()->SweepSingleByChannel(
	OutResult,
	CurrentLocation,
	CurrentLocation,
	FQuat::Identity,
	ECollisionChannel::ECC_GameTraceChannel1,
	Sphere,
	IgnoreParams
	)};

	if(!bHasFoundTarget)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("Actor Detected %s"),
		*OutResult.GetActor()->GetName());
}


// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

