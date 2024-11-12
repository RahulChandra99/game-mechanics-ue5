// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpellbreakCharacter.generated.h"

UCLASS()
class GAMEPLAYMECHANICS_API ASpellbreakCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASpellbreakCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	class UInteractionComponent* InteractionComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void PrimaryAttack();
	void PrimaryInteract();

	UPROPERTY(EditAnywhere, Category="Attack")
	UAnimMontage* AttackAnimMontage;

	FTimerHandle TimerHandle_PrimaryAttack;

	void PrimaryAttack_TimeElapsed();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
