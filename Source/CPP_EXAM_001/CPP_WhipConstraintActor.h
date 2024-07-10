// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <PhysicsEngine/PhysicsConstraintActor.h>
#include <PhysicsEngine/PhysicsConstraintComponent.h>
#include "CPP_WhipConstraintActor.generated.h"

UCLASS()
class CPP_EXAM_001_API ACPP_WhipConstraintActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_WhipConstraintActor();

    virtual void OnConstruction(const FTransform& Transform) override;

    UFUNCTION(BlueprintCallable, Category = "Whip")
    void AttachToPlayer(APawn* PlayerPawn, FName SocketName);

    UFUNCTION(BlueprintCallable, Category = "Whip")
    void WhipCrack();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Whip")
    float CrackForce = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Whip")
    float SegmentMass = 0.1f;

protected:
    // Number of segments in the whip
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Whip", meta = (ClampMin = "1", ClampMax = "20"))
    int32 NumSegments = 10;

    // Segm length
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Whip")
    float SegmentLength = 20.0f;

    // Mesh
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Whip")
    UStaticMesh* SegmentMeshClass;

    // Segm array
    UPROPERTY()
    TArray<UStaticMeshComponent*> WhipSegments;

    // Constraint array
    UPROPERTY()
    TArray<UPhysicsConstraintComponent*> Constraints;

private:
    UStaticMeshComponent* CreateWhipSegment(int32 SegmentIndex, UStaticMeshComponent* PreviousSegment);

    UPhysicsConstraintComponent* CreateConstraint(UStaticMeshComponent* PreviousSegment, UStaticMeshComponent* CurrentSegment, int32 ConstraintIndex);
};
