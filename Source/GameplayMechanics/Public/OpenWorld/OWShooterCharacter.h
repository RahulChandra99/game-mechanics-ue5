// Rahul Chandra All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OWShooterCharacter.generated.h"

class AOWGunActor;

UCLASS()
class GAMEPLAYMECHANICS_API AOWShooterCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);
	void StartJump();
	void StopJump();

	AOWGunActor* GunSpawn;

	UPROPERTY(EditAnywhere,Category="Gun")
	TSubclassOf<AOWGunActor> GunBPActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	AOWShooterCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
