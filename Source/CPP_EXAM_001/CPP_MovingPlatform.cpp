// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MovingPlatform.h"

// Sets default values
ACPP_MovingPlatform::ACPP_MovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;

    // Mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        PlatformMesh->SetStaticMesh(CubeMeshAsset.Object);
        PlatformMesh->SetRelativeScale3D(FVector(2.5f, 2.5f, 0.25f)); 
    }
}

void ACPP_MovingPlatform::BeginPlay()
{
	Super::BeginPlay();
    StartPoint = GetActorLocation();
    EndPoint = StartPoint + EndPoint;

    JourneyLength = (EndPoint - StartPoint).Size();
    CurrentVelocity = (EndPoint - StartPoint).GetSafeNormal() * Speed;
}

void ACPP_MovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (JourneyLength > 0)
    {
        FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
        SetActorLocation(NewLocation);

        JourneyTravelled += CurrentVelocity.Size() * DeltaTime;

        if (JourneyTravelled >= JourneyLength)
        {
            bReverse = !bReverse;
            CurrentVelocity = -CurrentVelocity;
            JourneyTravelled = 0;

            FVector Temp = StartPoint;
            StartPoint = EndPoint;
            EndPoint = Temp;
        }
    }
}

