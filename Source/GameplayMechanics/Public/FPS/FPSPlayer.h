// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSPlayer.generated.h"

UCLASS()
class GAMEPLAYMECHANICS_API AFPSPlayer : public ACharacter
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "FPS Character", meta = (AllowPrivateAccess = "True"))
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "FPS Character", meta = (AllowPrivateAccess = "True"))
	USkeletalMeshComponent* MeshFP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Sets default values for this character's properties
	AFPSPlayer();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCameraComponent* GetCameraComponent() { return CameraComp ;}

	USkeletalMeshComponent* GetMeshFP() { return MeshFP ;}

};
