// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorMechanics/HorrorCharacter.h"

// Sets default values
AHorrorCharacter::AHorrorCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHorrorCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}



// Called every frame
void AHorrorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHorrorCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(),Value);
}

void AHorrorCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix::Make(ControlRot).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(RightVector,Value);
}

void AHorrorCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * LookSensitivity);
}

void AHorrorCharacter::LookRight(float Value)
{
	AddControllerYawInput(Value * LookSensitivity);
}

// Called to bind functionality to input
void AHorrorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp",this,&AHorrorCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn",this,&AHorrorCharacter::LookRight);
	
	PlayerInputComponent->BindAxis("MoveForward",this,&AHorrorCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AHorrorCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);

}

