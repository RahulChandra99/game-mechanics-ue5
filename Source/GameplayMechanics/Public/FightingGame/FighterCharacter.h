// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FighterCharacter.generated.h"

UCLASS()
class GAMEPLAYMECHANICS_API AFighterCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Camera, meta =(AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Camera, meta =(AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	void StartAttack1();
	void StartAttack2();
	void StartAttack3();
	void StartAttack4();

public:
	// Sets default values for this character's properties
	AFighterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float Value);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
