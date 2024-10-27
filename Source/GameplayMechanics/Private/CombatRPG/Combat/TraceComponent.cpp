// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatRPG/Combat/TraceComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	
	
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    // Retrieve the start location of the trace based on the Start socket name from the skeletal mesh component
    FVector StartSocketLocation { SkeletalComp->GetSocketLocation(Start)};

    // Retrieve the end location of the trace based on the End socket name from the skeletal mesh component
    FVector EndSocketLocation { SkeletalComp->GetSocketLocation(End)};

    // Get the rotation of the socket used for shaping the collision box orientation
    FQuat ShapeRotation { SkeletalComp->GetSocketQuaternion(Rotation)};

    // Array to store all hit results when the trace detects collisions
    TArray<FHitResult> OutResults;

    // Calculate the distance between the start and end points of the trace
    double WeaponDistance = FVector::Distance(StartSocketLocation, EndSocketLocation);

    // Define the half extent of the collision box (dimensions) used for the trace
    // The box's width and height are defined by BoxCollisionLength, and its depth is based on the distance between the start and end points
    FVector BoxHalfExtent { BoxCollisionLength, BoxCollisionLength, WeaponDistance };
    
    // Divide the box extent by 2 to get the half extents, as needed for collision shape creation
    BoxHalfExtent /= 2;

    // Define the collision shape using the calculated half extents
    FCollisionShape Box{ FCollisionShape::MakeBox(BoxHalfExtent) };

    // Set up collision query parameters to ignore the owner of this component (so it doesn't detect itself)
    FCollisionQueryParams IgnoreParams{
        FName {TEXT("Ignore Params")}, // Optional name for the query
        false,                         // Trace complex collisions? (False here)
        GetOwner()                    // The owner to ignore during the trace
    };
    
    // Perform a sweep check along the path defined by StartSocketLocation and EndSocketLocation
    // The sweep checks if the collision box intersects with any object in the specified collision channel
    bool bHasFoundTarget = GetWorld()->SweepMultiByChannel(
        OutResults,             // Stores all objects hit by the sweep
        StartSocketLocation,    // Start of the sweep
        EndSocketLocation,      // End of the sweep
        ShapeRotation,          // Rotation applied to the collision box
        ECC_GameTraceChannel1,  // Collision channel to check (customizable based on your game setup)
        Box,                    // Collision shape (box) to sweep with
        IgnoreParams            // Parameters to ignore certain objects (like the owner)
    );

    // If debug mode is enabled, draw the collision box for visualization purposes
    if(bDebugMode)
    {
        // Calculate the center point of the box by interpolating between the start and end points
        FVector CentrePoint = UKismetMathLibrary::VLerp(StartSocketLocation, EndSocketLocation, 0.5f);
        
        // Draw the debug box using the calculated center point, box extents, and rotation
        // The box color changes based on whether a target was found (Green for hit, Red for no hit)
        UKismetSystemLibrary::DrawDebugBox(
            GetWorld(),
            CentrePoint,
            Box.GetExtent(),
            bHasFoundTarget ? FLinearColor::Green : FLinearColor::Red,
            ShapeRotation.Rotator(),
            1.f,  // Duration the box remains visible (1 second)
            2.f   // Line thickness for the debug box
        );
    }
}


