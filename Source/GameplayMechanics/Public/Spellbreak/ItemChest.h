// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayInterface.h"
#include "ItemChest.generated.h"


UCLASS()
class GAMEPLAYMECHANICS_API AItemChest : public AActor, public IGameplayInterface
{
	GENERATED_BODY()
	
private:
	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* LidMesh;

public:
	// Sets default values for this actor's properties
	AItemChest();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float TargetPitch;

};
