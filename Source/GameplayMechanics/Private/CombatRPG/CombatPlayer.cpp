// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatRPG/CombatPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "CombatRPG/Animations/CombatPlayerAnimInstance.h"
#include "CombatRPG/Combat/LockOnComponent.h"


// Sets default values
ACombatPlayer::ACombatPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	bUseControllerRotationYaw = false;

	// Initialize LockOnComponent
	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));
	

}

// Called when the game starts or when spawned
void ACombatPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Get the player's controller
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Subsystem
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem && CombatMappingContext)
		{
			// Add the Input Mapping Context (with a priority of 0)
			Subsystem->AddMappingContext(CombatMappingContext, 0);
		}
	}

	PlayerAnim = Cast<UCombatPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	
}

// Called every frame
void ACombatPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACombatPlayer::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(),Value);
}

void ACombatPlayer::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix::Make(ControlRot).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(RightVector,Value);
}

void ACombatPlayer::HandleLockOn()
{
	if(LockOnComponent)
	{
		bool bisLockedOnLocal = LockOnComponent->bisLockedOn;
		
		if(!bisLockedOnLocal)
		{
			LockOnComponent->StartLockOn();
			bisLockedOnLocal = true;
		}
		else if (bisLockedOnLocal)
		{
			LockOnComponent->EndLockOn();
			bisLockedOnLocal = false;
		}

		LockOnComponent->bisLockedOn = bisLockedOnLocal;
	}
}

// Called to bind functionality to input
void ACombatPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Cast to EnhancedInputComponent
	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PlayerInputComponent->BindAxis("MoveForward",this,&ACombatPlayer::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight",this,&ACombatPlayer::MoveRight);

		PlayerInputComponent->BindAxis("MoveForward",this,&ACombatPlayer::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight",this,&ACombatPlayer::MoveRight);

		// Bind Jump action
		if (JumpAction)
		{
			EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
			EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}

		//Bind Lock Action
		if(LockOnAction)
		{
			EnhancedInputComp->BindAction(LockOnAction, ETriggerEvent::Started,this,&ACombatPlayer::HandleLockOn);
		}

		PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
	}

	
}

