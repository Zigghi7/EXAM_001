// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"


ACPP_PlayerController::ACPP_PlayerController()
{}

void ACPP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	bAutoManageActiveCameraTarget = true;

	// Mouse input
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
}
