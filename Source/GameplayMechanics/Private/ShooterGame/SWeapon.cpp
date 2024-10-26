// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGame/SWeapon.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComp;
	
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASWeapon::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent, TEXT("Muzzle"));
	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	
	FVector End = Location + Rotation.Vector() * MaxRange;
	
	

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Location,
		End,
		ECC_GameTraceChannel2
	);

	if(bSuccess)
	{
		DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
	}
}

