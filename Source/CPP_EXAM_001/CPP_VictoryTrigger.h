//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "CPP_VictoryTrigger.generated.h"
//
//UCLASS()
//class CPP_EXAM_001_API ACPP_VictoryTrigger : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	ACPP_VictoryTrigger();
//
//protected:
//	virtual void BeginPlay() override;
//
//public:	
//	virtual void Tick(float DeltaTime) override;
//
//    UFUNCTION()
//    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
//        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
//        bool bFromSweep, const FHitResult& SweepResult);
//
//private:
//    UPROPERTY(VisibleAnywhere)
//    class UBoxComponent* CollisionComponent;
//
//    UPROPERTY(EditAnywhere, Category = "UI")
//    TSubclassOf<class UUserWidget> VictoryScreenClass;
//
//};
