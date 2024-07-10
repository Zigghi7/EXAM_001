// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Pawn.h"
#include "CPP_MovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CPP_SaveGame.h"

// Sets default values
ACPP_Pawn::ACPP_Pawn()
{
 	PrimaryActorTick.bCanEverTick = true;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Creo e imposta il CapsuleComponent come root
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	// Configuro capsule
	CapsuleComponent->SetCapsuleHalfHeight(88.0f);
	CapsuleComponent->SetCapsuleRadius(34.0f);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Block);


	// Attacca il MeshComponent al CapsuleComponent
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CapsuleComponent);
	// Regola la posizione
	MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	// Regola la rotazione della mesh
	MeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	// Regola la scala della mesh
	MeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	// Attacca SpringArmComponent al CapsuleComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	// Attacca il CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	
	// MovementComponent
	MovementComponent = CreateDefaultSubobject<UCPP_MovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(CapsuleComponent);

	// Animation Blueprint
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPClass(TEXT("/Game/Custom/Animation/ABP_PlayerPawn.ABP_PlayerPawn_C"));
	if (AnimBPClass.Succeeded())
	{
		AnimationBlueprintClass = AnimBPClass.Class;
	}

	// InteractionComponent
	InteractionComponent = CreateDefaultSubobject<UCPP_InteractionComponent>(TEXT("InteractionComponent"));

	SaveComponent = CreateDefaultSubobject<UCPP_SaveGame>(TEXT("SaveComponent"));

	bUseControllerRotationYaw = true;
}



void ACPP_Pawn::BeginPlay()
{
	Super::BeginPlay();
	// Setta la Mesh
	FString SkeletalMeshPath = "/Game/Custom/Meshes/SK_PlatformMesh.SK_PlatformMesh";
	PawnMesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
	if (PawnMesh)
	{
		MeshComponent->SetSkeletalMesh(PawnMesh);
		MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load SkeletalMesh"));
	}

	// Animation
	if (AnimationBlueprintClass)
	{
		MeshComponent->SetAnimInstanceClass(AnimationBlueprintClass);
		AnimInstance = MeshComponent->GetAnimInstance();
		if (!AnimInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create AnimInstance"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AnimationBlueprintClassis null"));
	}

	// Movement
	UCPP_MovementComponent* CustomMovement = Cast<UCPP_MovementComponent>(MovementComponent);
	if (!CustomMovement)
	{
		UE_LOG(LogTemp, Error, TEXT("Custom Movement Component is invalid"));
	}
	

}

void ACPP_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AnimInstance)
	{
		bool bIsInAir = MovementComponent->IsFalling();

		// Aggiorna IsInAir
		bIsInAir = MovementComponent->IsFalling();
		//AnimInstance->SetVariableBool(FName("IsInAir"), bIsInAir);
		
		// aggiorna Acceleration
		FVector Acceleration = MovementComponent->GetCurrentAcceleration();
		//AnimInstance->SetVariableVector(FName("Acceleration"), Acceleration);

	}
}

void ACPP_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Actions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_Pawn::Jump);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACPP_Pawn::Interact);
	PlayerInputComponent->BindAction("SavePosition", IE_Pressed, this, &ACPP_Pawn::SavePosition);
	PlayerInputComponent->BindAction("LoadPosition", IE_Pressed, this, &ACPP_Pawn::LoadPosition);

	// Axis
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ACPP_Pawn::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ACPP_Pawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACPP_Pawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPP_Pawn::AddControllerPitchInput);
}

void ACPP_Pawn::SavePosition()
{
	UE_LOG(LogTemp, Warning, TEXT("SavePosition Called"));

	FString SlotName = TEXT("MySaveSlot");
	int32 UserIndex = 0;

	bool bSuccess = SaveComponent->SaveGame(this, SlotName, UserIndex);

	if (bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Saved Successfully"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Save Game"));
	}
}

void ACPP_Pawn::LoadPosition()
{
	UE_LOG(LogTemp, Warning, TEXT("LoadPosition Called"));

	FString SlotName = TEXT("MySaveSlot");
	int32 UserIndex = 0;
	bool bSuccess = SaveComponent->LoadGame(this, SlotName, UserIndex);

	if (bSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Loaded Successfully"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Load Game"));
	}
}

void ACPP_Pawn::Jump()
{
	UE_LOG(LogTemp, Warning, TEXT("JumpAction Called"));

	if (MovementComponent)
	{
		MovementComponent->Jump();
	}
}

void ACPP_Pawn::Interact()
{
	if (InteractionComponent)
	{
		InteractionComponent->Interact();
	}
}

void ACPP_Pawn::MoveForward(float Input)
{


	if (MovementComponent && (Controller != nullptr) && (Input != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		MovementComponent->AddMovementInput(Direction, Input);
	}
}

void ACPP_Pawn::MoveRight(float Input)
{
	if (MovementComponent && (Controller != nullptr) && (Input != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		MovementComponent->AddMovementInput(Direction, Input);
	}
}

void ACPP_Pawn::Turn(float Rate)
{
	AddControllerYawInput(Rate);
}

void ACPP_Pawn::LookUp(float Rate)
{
	AddControllerPitchInput(Rate);
}
