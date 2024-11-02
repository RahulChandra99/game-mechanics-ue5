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

	void CharacterShoot();

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;
	float CurrentHealth;

	
	
public:

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
};
