// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS/FPSObjectiveActor.h"

#include "Components/SphereComponent.h"
#include "FPS/FPSPlayer.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	AFPSPlayer* MyCharacter = Cast<AFPSPlayer>(OtherActor);
	if(MyCharacter)
	{
		MyCharacter->bIsCarryingObjective = true;
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 
				15.f, 
				FColor::Blue, 
				FString::Printf(TEXT("Carrying Objective: %s"), MyCharacter->bIsCarryingObjective ? TEXT("True") : TEXT("False"))
			);
		}*/
		Destroy();
	}
}

void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

