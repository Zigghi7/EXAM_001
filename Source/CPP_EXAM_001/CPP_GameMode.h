// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Pawn.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPP_EXAM_001_API ACPP_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACPP_GameMode();

	virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // PlayerPawn RefFunc
    ACPP_Pawn* GetPlayerPawn() const { return PlayerPawn; }

protected:
    // PlayerPawn Ref
    UPROPERTY()
    ACPP_Pawn* PlayerPawn;

};