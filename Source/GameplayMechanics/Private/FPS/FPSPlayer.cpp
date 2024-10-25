// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS/FPSPlayer.h"

#include "Camera/CameraComponent.h"

// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	CameraComp->SetupAttachment(GetRootComponent());
	
	MeshFP = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFP"));
	MeshFP->SetupAttachment(CameraComp);
	MeshFP->SetOnlyOwnerSee(true);
	MeshFP->SetOwnerNoSee(false);
	MeshFP->SetCastShadow(false);
	MeshFP->SetReceivesDecals(false);
}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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

}

