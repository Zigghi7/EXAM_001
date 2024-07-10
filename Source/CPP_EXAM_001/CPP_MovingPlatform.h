// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_MovingPlatform.generated.h"

UCLASS()
class CPP_EXAM_001_API ACPP_MovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPP_MovingPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    FVector StartPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    FVector EndPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Speed = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bReverse = false;

private:
    FVector CurrentVelocity;
    float JourneyLength;
    float JourneyTravelled;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlatformMesh;
};
