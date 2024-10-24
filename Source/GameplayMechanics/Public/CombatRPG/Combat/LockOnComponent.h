// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockOnComponent, OnUpdatedTargetDelegate,
	AActor*, NewTargetActorRef
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYMECHANICS_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	ACharacter* OwnerRef;

	APlayerController* Controller;

	class UCharacterMovementComponent* MovementComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets default values for this component's properties
	ULockOnComponent();

	UFUNCTION(BlueprintCallable)
	void StartLockOn(float Radius = 750.f);

	UFUNCTION(BlueprintCallable)
	void EndLockOn();

	UPROPERTY(EditAnywhere)
	double BreakDistance { 1000.0 };

	AActor* CurrentTargetActor;

	class USpringArmComponent* SpringArmComp;
	
	bool bisLockedOn;

	UPROPERTY(BlueprintAssignable)
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;
};
