// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_WhipConstraintActor.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ACPP_WhipConstraintActor::ACPP_WhipConstraintActor()
{
	PrimaryActorTick.bCanEverTick = true;

    // Root
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    //Mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMeshFinder(TEXT("/Engine/BasicShapes/Cylinder"));
    if (CylinderMeshFinder.Succeeded())
    {
        SegmentMeshClass = CylinderMeshFinder.Object;
    }
}


void ACPP_WhipConstraintActor::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    for (auto* Segment : WhipSegments)
    {
        if (Segment) Segment->DestroyComponent();
    }
    for (auto* Constraint : Constraints)
    {
        if (Constraint) Constraint->DestroyComponent();
    }
    WhipSegments.Empty();
    Constraints.Empty();

    if (!SegmentMeshClass) return;

    UStaticMeshComponent* PreviousSegment = nullptr;
    for (int32 i = 0; i < NumSegments; i++)
    {
        UStaticMeshComponent* CurrentSegment = CreateWhipSegment(i, PreviousSegment);
        WhipSegments.Add(CurrentSegment);

        if (PreviousSegment)
        {
            UPhysicsConstraintComponent* Constraint = CreateConstraint(PreviousSegment, CurrentSegment, i - 1);
            Constraints.Add(Constraint);
        }

        PreviousSegment = CurrentSegment;
    }
}

void ACPP_WhipConstraintActor::AttachToPlayer(APawn* PlayerPawn, FName SocketName)
{
    if (PlayerPawn && !WhipSegments.IsEmpty())
    {
        USkeletalMeshComponent* PawnMesh = PlayerPawn->FindComponentByClass<USkeletalMeshComponent>();
        if (PawnMesh)
        {
            FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
            WhipSegments[0]->AttachToComponent(PawnMesh, AttachRules, SocketName);

            // No physics for first segm
            WhipSegments[0]->SetSimulatePhysics(false);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("SkeletalMeshComponent not finded"));
        }
    }
}

void ACPP_WhipConstraintActor::WhipCrack()
{
    if (WhipSegments.IsEmpty())
    {
        return;
    }

    UStaticMeshComponent* TipSegment = WhipSegments.Last();
    if (!TipSegment)
    {
        return;
    }

    FVector CrackDirection = TipSegment->GetForwardVector();
    CrackForce = 1000.0f;
    TipSegment->AddImpulse(CrackDirection * CrackForce);
}

UStaticMeshComponent* ACPP_WhipConstraintActor::CreateWhipSegment(int32 SegmentIndex, UStaticMeshComponent* PreviousSegment)
{
    UStaticMeshComponent* Segment = NewObject<UStaticMeshComponent>(this, *FString::Printf(TEXT("Segment_%d"), SegmentIndex));
    Segment->SetStaticMesh(SegmentMeshClass);
    Segment->SetupAttachment(SegmentIndex == 0 ? RootComponent : PreviousSegment);
    Segment->RegisterComponent();

    // Scaling and positioning
    float SegmentScale = (SegmentIndex == NumSegments - 1) ? 0.5f : 1.0f; // last segm is smaller
    Segment->SetRelativeScale3D(FVector(SegmentLength * SegmentScale, 0.05f, 0.05f));
    Segment->SetRelativeLocation(FVector(SegmentLength * SegmentIndex, 0, 0));
    Segment->SetRelativeRotation(FRotator(0, 0, 90));

    // Collisions
    Segment->SetSimulatePhysics(true);
    Segment->SetEnableGravity(true);
    Segment->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Segment->SetMassOverrideInKg(NAME_None, 0.1f, true); // light segm

    return Segment;
}

UPhysicsConstraintComponent* ACPP_WhipConstraintActor::CreateConstraint(UStaticMeshComponent* PreviousSegment, UStaticMeshComponent* CurrentSegment, int32 ConstraintIndex)
{
    UPhysicsConstraintComponent* Constraint = NewObject<UPhysicsConstraintComponent>(this, *FString::Printf(TEXT("Constraint_%d"), ConstraintIndex));
    Constraint->SetupAttachment(PreviousSegment);
    Constraint->RegisterComponent();
    Constraint->SetConstrainedComponents(PreviousSegment, NAME_None, CurrentSegment, NAME_None);

    // Constraints rules
    Constraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Limited, 10.0f);
    Constraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Limited, 10.0f);
    Constraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, 10.0f);
    Constraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, 60.0f);
    Constraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Limited, 60.0f);
    Constraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Limited, 60.0f);

    return Constraint;
}