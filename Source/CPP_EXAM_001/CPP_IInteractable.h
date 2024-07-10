// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_IInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UCPP_IInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CPP_EXAM_001_API ICPP_IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);
};
