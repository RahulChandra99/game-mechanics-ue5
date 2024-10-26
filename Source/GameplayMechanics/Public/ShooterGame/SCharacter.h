// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class ASWeapon;

UCLASS()
class GAMEPLAYMECHANICS_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void BeginCrouch();
	void EndCrouch();

	void StartShootingGun();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASWeapon> WeaponClass;

	UPROPERTY()
	ASWeapon* Weapon;
	

public:
    // Sets default values for this character's properties
	ASCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
