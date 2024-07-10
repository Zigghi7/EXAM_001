// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_EXAM_001_API UCPP_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values
	UCPP_InteractionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionDistance = 200.0f;

private:
	class ACPP_Pawn* PlayerPawn;

		
};
