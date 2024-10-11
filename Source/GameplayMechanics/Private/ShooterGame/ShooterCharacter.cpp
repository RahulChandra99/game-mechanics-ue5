// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGame/ShooterCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a Camera Boom (pulls in towards the character if there is a collision
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach camera to end of boom
	FollowCamera->bUsePawnControlRotation = false; // Camera doesnt rotate relative to arm

	

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void AShooterCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// Get the forward direction based on the controller's rotation
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
        
		// Move the character forward
		AddMovementInput(ForwardDirection, Value);
	}
}

void AShooterCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// Get the right direction based on the controller's rotation
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
        
		// Move the character right
		AddMovementInput(RightDirection, Value);
	}
}

void AShooterCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); // units : deg/sec * sec/frame
}

void AShooterCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds()); // units : deg/sec * sec/frame
}



// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);

}

