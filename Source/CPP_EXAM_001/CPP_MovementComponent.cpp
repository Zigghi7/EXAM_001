// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

UCPP_MovementComponent::UCPP_MovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    PreviousVelocity = FVector::ZeroVector;
    LastUpdateTime = 0.0f;
    CurrentAcceleration = FVector::ZeroVector;
}

void UCPP_MovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }

    float CurrentTime = GetWorld()->GetTimeSeconds();

    // Accelleration
    if (DeltaTime > 0.0f)
    {
        CurrentAcceleration = (CurrentVelocity - PreviousVelocity) / DeltaTime;
    }

    FVector DesiredMovementThisFrame = CurrentInputVector.GetClampedToMaxSize(1.0f) * MaxSpeed * DeltaTime;

    if (!DesiredMovementThisFrame.IsNearlyZero())
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

        if (Hit.IsValidBlockingHit())
        {
            SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
        }
        //CurrentVelocity = DesiredMovementThisFrame / DeltaTime;
    }
    else
    {
        CurrentVelocity = FMath::VInterpTo(CurrentVelocity, FVector::ZeroVector, DeltaTime, 5.0f);
    }

    // Gravity
    CurrentVelocity.Z -= Gravity * DeltaTime;

    // VerticalMovement
    FVector VerticalMovement = FVector(0, 0, CurrentVelocity.Z * DeltaTime);
    FHitResult HitResult;
    SafeMoveUpdatedComponent(VerticalMovement, UpdatedComponent->GetComponentRotation(), true, HitResult);

    if (HitResult.IsValidBlockingHit())
    {
        // If hits something, stop VerticalMovement
        CurrentVelocity.Z = 0;
        bIsJumping = false;
    }
    else
    {
        bIsJumping = true;
    }

    // Refresh values
    PreviousVelocity = CurrentVelocity;
    LastUpdateTime = CurrentTime;

    // Reset Input after perform
    CurrentInputVector = FVector::ZeroVector;
}
bool UCPP_MovementComponent::IsFalling() const
{
    return bIsJumping;
}

bool UCPP_MovementComponent::IsGrounded() const
{
    return !bIsJumping;
}
void UCPP_MovementComponent::AddInputVector(FVector WorldVector, bool bForce)
{
    InputVector += WorldVector;
}

FVector UCPP_MovementComponent::GetCurrentAcceleration() const
{
    return CurrentAcceleration;
}

FVector UCPP_MovementComponent::GetVelocity() const
{
    return CurrentVelocity;
}

FVector UCPP_MovementComponent::ComputeSlideVector(const FVector& Delta, const float Time, const FVector& Normal, const FHitResult& Hit) const
{
    FVector Result = FVector::VectorPlaneProject(Delta, Normal) * Time;

    if (Result.SizeSquared() < FMath::Square(0.01f))
    {
        Result = FVector::ZeroVector;
    }

    return Result;
}

float UCPP_MovementComponent::SlideAlongSurface(const FVector& Delta, float Time, const FVector& Normal, FHitResult& Hit, bool bHandleImpact)
{
    if (!Hit.bBlockingHit)
    {
        return 0.f;
    }

    FVector SlideVector = ComputeSlideVector(Delta, Time, Normal, Hit);

    if (!SlideVector.IsNearlyZero())
    {
        FHitResult NewHit(1.f);

        SafeMoveUpdatedComponent(SlideVector, UpdatedComponent->GetComponentRotation(), true, NewHit);

        if (NewHit.bBlockingHit)
        {
            if (bHandleImpact)
            {
                HandleImpact(NewHit, Time, SlideVector);
            }

            return SlideAlongSurface(SlideVector, 1.f - NewHit.Time, NewHit.Normal, NewHit, false);
        }
    }

    return Time;
}

void UCPP_MovementComponent::HandleImpact(const FHitResult& Hit, float TimeSlice, const FVector& MoveDelta)
{
    if (Hit.bBlockingHit)
    {
        CurrentVelocity = FVector::VectorPlaneProject(CurrentVelocity, Hit.Normal);
    }
}

void UCPP_MovementComponent::FindFloor(const FVector& CapsuleLocation, FCustomFindFloorResult& OutFloorResult, bool bZeroDelta, const FHitResult* DownwardSweepResult)
{
    FHitResult Hit(1.f);
    FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(FindFloor), false, GetOwner());
    FCollisionResponseParams ResponseParam;
    InitCollisionParams(QueryParams, ResponseParam);

    const float FloorSweepTraceDist = 100.f; 
    const FVector Start = CapsuleLocation;
    const FVector End = Start - FVector(0.f, 0.f, FloorSweepTraceDist);

    bool bBlockingHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, QueryParams, ResponseParam);


    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f);


    if (bBlockingHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Floor detected at distance: %f"), Hit.Distance);
        OutFloorResult.SetFromLineTrace(Hit, FloorSweepTraceDist, 0.f, true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No floor detected"));
        OutFloorResult.Clear();
    }
}

void UCPP_MovementComponent::AddMovementInput(FVector Direction, float Value)
{
    CurrentInputVector += Direction * Value;
}

void UCPP_MovementComponent::Jump()
{
    if (!bIsJumping)
    {
        CurrentVelocity.Z = JumpForce;
        bIsJumping = true;
    }
}

