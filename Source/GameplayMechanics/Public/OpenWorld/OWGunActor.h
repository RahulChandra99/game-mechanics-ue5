// Rahul Chandra All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OWGunActor.generated.h"

UCLASS()
class GAMEPLAYMECHANICS_API AOWGunActor : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AOWGunActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

private:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* GunMuzzle;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* GunImpactEffect;
	
public:
	void GunShoot();
	

};
