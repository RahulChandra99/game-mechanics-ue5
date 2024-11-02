// Rahul Chandra All Rights Reserved


#include "OpenWorld/OWShooterCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "OpenWorld/OWGunActor.h"

// Sets default values
AOWShooterCharacter::AOWShooterCharacter()
{
	// Set this character to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Create Camera Arm (Spring Arm) and attach it to the Root Component
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	CameraArm->SetupAttachment(RootComponent);

	// Adjust the length of the arm (distance from character)
	CameraArm->TargetArmLength = 300.0f;  // Distance of the camera from the character
	CameraArm->SocketOffset = FVector(0.0f, 50.0f, 60.0f);  // Offset from character center
	CameraArm->bUsePawnControlRotation = true;  // Rotate the arm based on the character's rotation

	// Create Camera and attach it to the Camera Arm
	Camera = CreateDefaultSubobject<UCameraComponent>("TPSCamera");
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	// Set camera settings
	Camera->bUsePawnControlRotation = false;  // Camera does not rotate with controller
	Camera->SetFieldOfView(90.0f);  // Set a wide FOV for shooter perspective

	// Character rotation settings to follow the camera direction
	bUseControllerRotationYaw = false;  // Let the controller handle rotation
	GetCharacterMovement()->bOrientRotationToMovement = true;  // Rotate character to movement direction
}




// Called when the game starts or when spawned
void AOWShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	GunSpawn = GetWorld()->SpawnActor<AOWGunActor>(GunBPActor);
	GunSpawn->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, TEXT("gun_socket_r"));
	GunSpawn->SetOwner(this);

	CurrentHealth = MaxHealth;
}

// Called every frame
void AOWShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOWShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AOWShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&AOWShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"),this,&AOWShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"),this,&AOWShooterCharacter::LookRight);

	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&AOWShooterCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Released,this,&AOWShooterCharacter::StopJump);
	PlayerInputComponent->BindAction(TEXT("Shoot"),IE_Pressed,this,&AOWShooterCharacter::CharacterShoot);
	//PlayerInputComponent->BindAction(TEXT("Shoot"),IE_Released,this,&AOWShooterCharacter::StopJump);
}


void AOWShooterCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(),Value);
}

void AOWShooterCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix::Make(ControlRot).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(RightVector,Value);
}

void AOWShooterCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AOWShooterCharacter::LookRight(float Value)
{
	AddControllerYawInput(Value);
}

void AOWShooterCharacter::StartJump()
{
	ACharacter::Jump();
}

void AOWShooterCharacter::StopJump()
{
	ACharacter::StopJumping();
}

void AOWShooterCharacter::CharacterShoot()
{
	GunSpawn->GunShoot();
}



float AOWShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                      AActor* DamageCauser)
{
	float AppliedDamage =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AppliedDamage = FMath::Min(CurrentHealth,AppliedDamage);
	CurrentHealth -= AppliedDamage;

	UE_LOG(LogTemp,Warning,TEXT("%f"),CurrentHealth);
	
	return AppliedDamage;
	
}

bool AOWShooterCharacter::IsDead() const
{
	return CurrentHealth <= 0.f;
}