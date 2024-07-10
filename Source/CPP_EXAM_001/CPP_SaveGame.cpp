#include "CPP_SaveGame.h"
#include "Kismet/GameplayStatics.h"

bool UCPP_SaveGame::SaveGame(AActor* ActorToSave, FString SlotName, int32 UserIndex)
{
    if (!ActorToSave)
    {
        return false;
    }

    UCPP_SaveGame* SaveGameInstance = Cast<UCPP_SaveGame>(UGameplayStatics::CreateSaveGameObject(UCPP_SaveGame::StaticClass()));
    if (SaveGameInstance)
    {
        // Save
        SaveGameInstance->PlayerLocation = ActorToSave->GetActorLocation();
        SaveGameInstance->PlayerRotation = ActorToSave->GetActorRotation();

        return UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, UserIndex);
    }

    return false;
}

bool UCPP_SaveGame::LoadGame(AActor* ActorToLoad, FString SlotName, int32 UserIndex)
{
    if (!ActorToLoad)
    {
        return false;
    }

    UCPP_SaveGame* LoadedGame = Cast<UCPP_SaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
    if (LoadedGame)
    {
        // Load
        ActorToLoad->SetActorLocation(LoadedGame->PlayerLocation);
        ActorToLoad->SetActorRotation(LoadedGame->PlayerRotation);

        return true;
    }

    return false;
}

