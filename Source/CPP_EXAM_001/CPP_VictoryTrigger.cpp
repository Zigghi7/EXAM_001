//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "CPP_VictoryTrigger.h"
//#include "CPP_Pawn.h"
//#include "Components/BoxComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "Blueprint/UserWidget.h"
//
//// Sets default values
//ACPP_VictoryTrigger::ACPP_VictoryTrigger()
//{
//	PrimaryActorTick.bCanEverTick = true;
//
//	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
//	RootComponent = CollisionComponent;
//	//CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AVictoryTrigger::OnOverlapBegin);
//}
//
//void ACPP_VictoryTrigger::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//void ACPP_VictoryTrigger::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//void ACPP_VictoryTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//    if (OtherActor && (OtherActor != this) && OtherComp)
//    {
//        // Check if the overlapping actor is the player
//        if (OtherActor->IsA(ACPP_Pawn::StaticClass()))
//        {
//            // Display the victory screen
//            if (VictoryScreenClass)
//            {
//                UUserWidget* VictoryScreen = CreateWidget<UUserWidget>(GetWorld(), VictoryScreenClass);
//                if (VictoryScreen)
//                {
//                    VictoryScreen->AddToViewport();
//                    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//                    if (PlayerController)
//                    {
//                        FInputModeUIOnly InputMode;
//                        PlayerController->SetInputMode(InputMode);
//                        PlayerController->bShowMouseCursor = true;
//                    }
//                }
//            }
//        }
//    }
//}
//
