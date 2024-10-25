// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

UCLASS()
class GAMEPLAYMECHANICS_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereComp;

	void PlayEffects();

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* PickupFX; 

public:	

// Sets default values for this actor's properties
	AFPSObjectiveActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
