// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_MyBlueprintFunctionLibrary.h"
#include "GameFramework//Character.h"

//void UCPP_MyBlueprintFunctionLibrary::BindInput(ACharacter* Character)
//{
//	/*UInputComponent* Input = Character->InputComponent;
//	if (Input)
//	{
//		Input->BindAction(FName("Jump"), EInputEvent::IE_Pressed, Character, &ACharacter::Jump);
//	}*/
//}
//
//bool UCPP_MyBlueprintFunctionLibrary::GetActorLocation(AActor* Actor, FVector& Location)
//{
//	if (!Actor||!Actor->GetRootComponent())
//	{
//		return false;
//	}
//
//	Location = Actor->GetActorLocation();
//	return true;
//
//}
//
//bool UCPP_MyBlueprintFunctionLibrary::SetActorLocation(AActor* Actor, FVector Location)
//{
//	return Actor->SetActorLocation(Location);
//
//}
//
//bool UCPP_MyBlueprintFunctionLibrary::JumpActionCharacter(ACharacter* Character)
//{
//	if (!Character) return false;
//	Character->Jump();
//	return true;
//}
