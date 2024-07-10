// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CPP_MovementComponent.generated.h"

USTRUCT()
struct FCustomFindFloorResult
{
    GENERATED_USTRUCT_BODY()
	FHitResult HitResult;
	bool bWalkableFloor;
	float FloorDist;
	float LineDist;

	FCustomFindFloorResult() : bWalkableFloor(false), FloorDist(0.f), LineDist(0.f) {}

    void Clear()
    {
        HitResult = FHitResult();
        bWalkableFloor = false;
        FloorDist = 0.f;
        LineDist = 0.f;
    }

    void SetFromLineTrace(const FHitResult& InHitResult, const float InSweepFloorDist, const float InLineDist, bool bIsWalkableFloor)
    {
        HitResult = InHitResult;
        bWalkableFloor = bIsWalkableFloor;
        FloorDist = InSweepFloorDist;
        LineDist = InLineDist;
    }

	bool IsWalkableFloor() const { return bWalkableFloor; }
};
UCLASS()
class CPP_EXAM_001_API UCPP_MovementComponent : public UMovementComponent
{
    GENERATED_BODY()
public:
    UCPP_MovementComponent();

    void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction);

    void AddInputVector(FVector WorldVector, bool bForce = false);
    void AddMovementInput(FVector Direction, float Value);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void Jump();

    UFUNCTION(BlueprintPure, Category = "Movement")
    bool IsFalling() const;
    bool IsGrounded() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    FVector GetCurrentAcceleration() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    FVector GetVelocity() const ;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MaxSpeed = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Acceleration = 2000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Deceleration = 2000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float JumpForce = 550.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Gravity = 980.0f;


private:
    FVector CurrentVelocity;
    FVector InputVector;
    FVector CurrentInputVector;
    bool bIsJumping = false;
    FVector PreviousVelocity;
    float LastUpdateTime;
    FVector CurrentAcceleration;

    
    void FindFloor(const FVector& CapsuleLocation, FCustomFindFloorResult& OutFloorResult, bool bZeroDelta, const FHitResult* DownwardSweepResult = nullptr);

    FVector ComputeSlideVector(const FVector& Delta, const float Time, const FVector& Normal, const FHitResult& Hit) const;

    virtual float SlideAlongSurface(const FVector& Delta, float Time, const FVector& Normal, FHitResult& Hit, bool bHandleImpact = true) override;

    void HandleImpact(const FHitResult& Hit, float TimeSlice, const FVector& MoveDelta);

};

