#include "CPP_GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "CPP_PlayerController.h"
#include "CPP_Pawn.h"

ACPP_GameMode::ACPP_GameMode()
{
    PrimaryActorTick.bCanEverTick = true;

    DefaultPawnClass = ACPP_Pawn::StaticClass();
    PlayerControllerClass = ACPP_PlayerController::StaticClass();
}

void ACPP_GameMode::BeginPlay()
{
    Super::BeginPlay();

}

void ACPP_GameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //UPDATE LOGIC 
}

