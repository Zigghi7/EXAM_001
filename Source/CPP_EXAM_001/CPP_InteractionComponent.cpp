// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_InteractionComponent.h"
#include "CPP_IInteractable.h"
#include "CPP_Pawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
UCPP_InteractionComponent::UCPP_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UCPP_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = Cast<ACPP_Pawn>(GetOwner());
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("InteractionComponent not finded"));
	}
}

void UCPP_InteractionComponent::Interact()
{
    if (!PlayerPawn)
    {
        return;
    }

    FVector Start = PlayerPawn->GetActorLocation();
    FVector End = Start + PlayerPawn->GetActorForwardVector() * InteractionDistance;

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(PlayerPawn);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *HitActor->GetName());
            if (HitActor->Implements<UCPP_IInteractable>())
            {
                ICPP_IInteractable::Execute_Interact(HitActor, PlayerPawn);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Actor does not implement IInteractable"));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Line trace did not hit anything"));
    }
    
}

