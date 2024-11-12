// Rahul Chandra All Rights Reserved


#include "Spellbreak/InteractionComponent.h"

#include "QuickDebug.h"
#include "Spellbreak/GameplayInterface.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);

	FVector EndLocation = EyeLocation +(EyeRotation.Vector() * 1000);
	
	//FHitResult Hit;
	/*bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(
		Hit,
		EyeLocation,
		EndLocation,
		ObjectQueryParams
		);*/

	float Radius = 30.f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	
	TArray<FHitResult> Hits;
	bool bBlockingHits = GetWorld()->SweepMultiByObjectType(
		Hits,
		EyeLocation,
		EndLocation,
		FQuat::Identity,
		ObjectQueryParams,
		Shape
		);

	FColor LineColor = bBlockingHits ? FColor::Green : FColor::Red;
	
	for(FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->Implements<UGameplayInterface>())
		{
		
			APawn* MyPawn = Cast<APawn>(MyOwner);
			if (MyPawn)
			{
				IGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}

		DrawDebugSphere(GetWorld(),Hit.ImpactPoint,Radius,32,LineColor,false,2.f);
	}
	
	DrawDebugLine(GetWorld(),EyeLocation,EndLocation,LineColor,false,2.f,0,2.f);
	
}

