// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatRPG/Combat/TraceComponent.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	
	
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector StartSocketLocation { SkeletalComp->GetSocketLocation(Start)};
	FVector EndSocketLocation { SkeletalComp->GetSocketLocation(End)};
	FQuat ShapeRotation { SkeletalComp->GetSocketQuaternion(Rotation)};

	TArray<FHitResult> OutResults;
	double WeaponDistance = FVector::Distance(StartSocketLocation,EndSocketLocation);
	FVector BoxHalfExtent { BoxCollisionLength, BoxCollisionLength, WeaponDistance};
	BoxHalfExtent /= 2;
	FCollisionShape Box{
		FCollisionShape::MakeBox(BoxHalfExtent)
	};

	FCollisionQueryParams IgnoreParams{
		FName {TEXT("Ignore Params")},
		false,
		GetOwner()
	};
	
	bool bHasFoundTarget = GetWorld()->SweepMultiByChannel(
		OutResults,
		StartSocketLocation,
		EndSocketLocation,
		ShapeRotation,
		ECC_GameTraceChannel1,
		Box,
		IgnoreParams
	);

	if(bHasFoundTarget)
	{
		UE_LOG(
		LogTemp,
		Warning,
		TEXT("Target Found")		
		);
	}
	
	
}

