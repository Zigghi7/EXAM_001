// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CPP_SaveGame.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSaveData {
	GENERATED_BODY()
};


/**
 * 
 */
UCLASS()
class CPP_EXAM_001_API UCPP_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	//UCPP_SaveGame();


	UPROPERTY(BlueprintReadWrite)
	FVector PlayerLocation;
	UPROPERTY(BlueprintReadWrite)
	FRotator PlayerRotation;

	UPROPERTY(BlueprintReadWrite)
	FPlayerSaveData PlayerSaveData;

	UFUNCTION(BlueprintCallable, Category = "Save Game")
	bool SaveGame(AActor* ActorToSave, FString SlotName, int32 UserIndex);

	UFUNCTION(BlueprintCallable, Category = "Save Game")
	bool LoadGame(AActor* ActorToLoad, FString SlotName, int32 UserIndex);


};
