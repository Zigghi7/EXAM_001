// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_IInteractable.h"
#include "UObject/ConstructorHelpers.h"
#include "CPP_InteractiveDoor.generated.h"


UCLASS()
class CPP_EXAM_001_API ACPP_InteractiveDoor : public AActor, public ICPP_IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values
	ACPP_InteractiveDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
    class USceneComponent* DoorRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
    class UStaticMeshComponent* DoorMesh;

    UFUNCTION(BlueprintCallable, Category = "Door")
    void OpenDoor();

    UFUNCTION(BlueprintCallable, Category = "Door")
    void CloseDoor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    float OpenAngle = 90.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
    float OpenSpeed = 2.0f;

    // Interface Implementation
    virtual void Interact_Implementation(AActor* Interactor) override;

private:
    bool bIsOpen = false;
    FRotator InitialRotation;
    FRotator TargetRotation;
};