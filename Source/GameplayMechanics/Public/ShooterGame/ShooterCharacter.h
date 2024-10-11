// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class GAMEPLAYMECHANICS_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	/*@param Rate This is a normalized rate i.e 1.0 means 100% of desired turn rate*/
	void TurnAtRate(float Rate);

	/*@param Rate This is a normalized rate i.e 1.0 means 100% of desired turn rate*/
	void LookUpAtRate(float Rate);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
private:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta =(AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/* Camera that follow the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta =(AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/*Base turn rate in deg/sec*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta =(AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/*Base look up/down rate in deg/sec*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta =(AllowPrivateAccess = "true"))
	float BaseLookUpRate;

public:

	/* Return Cameraboom subobject */
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/* Return FollowCamera subobject */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
