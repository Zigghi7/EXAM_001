// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_InteractiveDoor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACPP_InteractiveDoor::ACPP_InteractiveDoor()
{
	PrimaryActorTick.bCanEverTick = true;

    // Root
    DoorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DoorRoot"));
    RootComponent = DoorRoot;

    // Pivot
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(DoorRoot);
    DoorMesh->SetRelativeLocation(FVector(-50.0f, 0.0f, 0.0f));////////////////////

    // Mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        DoorMesh->SetStaticMesh(CubeMeshAsset.Object);
        DoorMesh->SetRelativeScale3D(FVector(0.2f, 1.0f, 2.0f)); 
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
    if (DefaultMaterial.Succeeded())
    {
        DoorMesh->SetMaterial(0, DefaultMaterial.Object);
    }

    // Collisions
    DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    DoorMesh->SetCollisionObjectType(ECC_WorldDynamic);
    DoorMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    
}

void ACPP_InteractiveDoor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialRotation = DoorRoot->GetRelativeRotation();
	TargetRotation = InitialRotation;
}

void ACPP_InteractiveDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FRotator CurrentRotation = DoorRoot->GetRelativeRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, OpenSpeed);


    if (!CurrentRotation.Equals(NewRotation, 0.1f))
    {
        DoorRoot->SetRelativeRotation(NewRotation);
    }
}

void ACPP_InteractiveDoor::OpenDoor()
{
    if (!bIsOpen)
    {
        TargetRotation = InitialRotation + FRotator(0, OpenAngle, 0);
        bIsOpen = true;
    }
}

void ACPP_InteractiveDoor::CloseDoor()
{
    if (bIsOpen)
    {
        TargetRotation = InitialRotation;
        bIsOpen = false;
    }
}

void ACPP_InteractiveDoor::Interact_Implementation(AActor* Interactor)
{
    if (bIsOpen)
    {
        UE_LOG(LogTemp, Warning, TEXT("Closing door"));
        CloseDoor();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Opening door"));
        OpenDoor();
    }
}
