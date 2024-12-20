// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

UCLASS()
class GAMEPLAYMECHANICS_API ASWeapon : public AActor
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkeletalMeshComponent* MeshComponent;

	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10.f;
public:
	// Sets default values for this actor's properties
	ASWeapon();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

};
