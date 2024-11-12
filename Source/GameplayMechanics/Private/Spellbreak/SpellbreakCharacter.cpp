// Fill out your copyright notice in the Description page of Project Settings.


#include "Spellbreak/SpellbreakCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Spellbreak/InteractionComponent.h"

#include "QuickDebug.h"

// Sets default values
ASpellbreakCharacter::ASpellbreakCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 250.f;
	SpringArmComponent->SocketOffset = FVector(0.f,90.f,0.f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	
	bUseControllerRotationYaw = false;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComp");

}

// Called when the game starts or when spawned
void ASpellbreakCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpellbreakCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(),Value);
}

void ASpellbreakCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix::Make(ControlRot).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(RightVector,Value);
}




// Called every frame
void ASpellbreakCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpellbreakCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASpellbreakCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASpellbreakCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Shoot",IE_Pressed,this,&ASpellbreakCharacter::PrimaryAttack);

	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&ASpellbreakCharacter::PrimaryInteract);

}

void ASpellbreakCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnimMontage);
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASpellbreakCharacter::PrimaryAttack_TimeElapsed,0.2f);
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ASpellbreakCharacter::PrimaryAttack_TimeElapsed()
{
	
	
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	
	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

void ASpellbreakCharacter::PrimaryInteract()
{
	if(!InteractionComponent) return;
	
	InteractionComponent->PrimaryInteract();
}

