// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);

class UDamageType;
class AController;
class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEPLAYMECHANICS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	float CurrentHealth;

	UFUNCTION()
	void OnOwnerTakenDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UHealthComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Health")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Health")
	float StartingHealth;

	UFUNCTION(BlueprintPure,Category ="Health")
	float GetCurrentHealth();

	UFUNCTION(BlueprintPure,Category ="Health")
	bool GetIsDead();

	UPROPERTY(BlueprintAssignable,Category ="Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable,Category ="Health")
	FOnDied OnDied;
};
