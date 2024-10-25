// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS/FPSPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComp->SetupAttachment(GetRootComponent());
	CameraComp->SetRelativeLocation(FVector(0, 0, BaseEyeHeight)); // Position the camera
	CameraComp->bUsePawnControlRotation = true;
	
	MeshFP = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFP"));
	MeshFP->SetupAttachment(CameraComp);
	MeshFP->SetOnlyOwnerSee(true);
	MeshFP->SetOwnerNoSee(false);
	MeshFP->SetCastShadow(false);
	MeshFP->SetReceivesDecals(false);
	MeshFP->SetRelativeRotation(FRotator(2.0f, -15.0f, 5.0f));
	MeshFP->SetRelativeLocation(FVector(0, 0, -160.0f));

	GetMesh()->SetOnlyOwnerSee(false);
	GetMesh()->SetOwnerNoSee(true);

	
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AFPSPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&AFPSPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"),this,&AFPSPlayer::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"),this,&AFPSPlayer::Turn);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"),this,&AFPSPlayer::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this,&AFPSPlayer::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,&AFPSPlayer::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Released,this,&ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Sprint"),IE_Pressed,this,&AFPSPlayer::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"),IE_Released,this,&AFPSPlayer::StopSprint);
	
}


void AFPSPlayer::MoveForward(float Value)
{
	if(Value != 0.0)
	{
		AddMovementInput(GetActorForwardVector(),Value);
	}
	else
	{
		StopSprint();
	}
}

void AFPSPlayer::MoveRight(float Value)
{
	if(Value != 0.0)
	{
		AddMovementInput(GetActorRightVector(),Value);
	}
}

void AFPSPlayer::MoveUp(float Value)
{
	if(Value != 0.0)
	{
		AddMovementInput(GetActorUpVector(),Value);
	}
}

void AFPSPlayer::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AFPSPlayer::TurnRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPSPlayer::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AFPSPlayer::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookRate * GetWorld()->GetDeltaSeconds());
}

void AFPSPlayer::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void AFPSPlayer::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

