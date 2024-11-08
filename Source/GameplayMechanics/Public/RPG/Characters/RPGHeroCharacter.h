// Rahul Chandra All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "RPG/Characters/RPGBaseCharacter.h"
#include "RPGHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;


UCLASS()
class GAMEPLAYMECHANICS_API ARPGHeroCharacter : public ARPGBaseCharacter
{
	GENERATED_BODY()

private:

	ARPGHeroCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera",meta = (AllowPrivateAccess))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera",meta = (AllowPrivateAccess))
	UCameraComponent* FollowCamera;

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
