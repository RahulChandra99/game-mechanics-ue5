// Rahul Chandra All Rights Reserved


#include "OpenWorld/OWGunActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AOWGunActor::AOWGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);
	
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void AOWGunActor::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AOWGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOWGunActor::GunShoot()
{
	UGameplayStatics::SpawnEmitterAttached(GunPS, GunMesh, TEXT("Muzzle"));
	
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
		ECC_GameTraceChannel3
	);

	if(bSuccess)
	{
		DrawDebugPoint(GetWorld(),Hit.Location,20.f,FColor::Red,true);
	}
}

