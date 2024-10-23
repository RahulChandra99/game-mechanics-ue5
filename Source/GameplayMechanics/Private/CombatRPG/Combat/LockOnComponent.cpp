// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatRPG/Combat/LockOnComponent.h"
#include "DrawDebugHelpers.h"
#include "CombatRPG/Interfaces/Enemy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	OwnerRef = GetOwner<ACharacter>();
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComponent = OwnerRef->GetCharacterMovement();

	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();
	
}


// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!IsValid(CurrentTargetActor)) { return; }

	FVector CurrentLocation { OwnerRef->GetActorLocation() };
	FVector TargetLocation { CurrentTargetActor->GetActorLocation() };

	double TargetDistance {
		FVector::Distance(CurrentLocation, TargetLocation)
	};

	if(TargetDistance >= BreakDistance)
	{
		EndLockOn();
		return;
	}
	
	TargetLocation.Z -= 125;
	
	FRotator NewRotation { UKismetMathLibrary::FindLookAtRotation(CurrentLocation,TargetLocation) } ;

	Controller->SetControlRotation(NewRotation);

	
	
}

void ULockOnComponent::StartLockOn(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FCollisionShape Sphere { FCollisionShape::MakeSphere(Radius)};
	FCollisionQueryParams IgnoreParams{
		FName { TEXT("Ignore Collision Params")},
		false,
		OwnerRef
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
	
	if(!bHasFoundTarget) { return; }

	//validation of enemy interface
	if (!OutResult.GetActor()->Implements<UEnemy>()) { return;}

	CurrentTargetActor = OutResult.GetActor();
	
	Controller->SetIgnoreLookInput(true);
	MovementComponent->bOrientRotationToMovement = false;
	MovementComponent->bUseControllerDesiredRotation = true;

	SpringArmComp->TargetOffset = FVector { 0.f,0.f,100.f};

	IEnemy::Execute_OnSelect(CurrentTargetActor);
	
}

void ULockOnComponent::EndLockOn()
{
	IEnemy::Execute_OnDeselect(CurrentTargetActor);
	
	CurrentTargetActor = nullptr;
	
	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->bUseControllerDesiredRotation = false;
	SpringArmComp->TargetOffset = FVector::ZeroVector;
	
	Controller->ResetIgnoreLookInput();
	
	bisLockedOn = false;
}

