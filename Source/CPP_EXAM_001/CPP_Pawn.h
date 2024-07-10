#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_MovementComponent.h"
#include "CPP_InteractionComponent.h"
#include "CPP_SaveGame.h"
#include "Components/SkeletalMeshComponent.h"
#include "CPP_Pawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UCPP_MovementComponent;
class UCPP_InteractionComponent;


UCLASS()
class CPP_EXAM_001_API ACPP_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_Pawn();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// CapsuleComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* CapsuleComponent;

	// MeshComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* MeshComponent;
	UPROPERTY()
	class USkeletalMesh* PawnMesh;

	// Camera&SpringArmComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	//MovementComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCPP_MovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpZVelocity = 500.0f;

	// InteractionComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UCPP_InteractionComponent* InteractionComponent;

	// AnimationComponent
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TSubclassOf<UAnimInstance> AnimationBlueprintClass;

	UPROPERTY()
	class UAnimInstance* AnimInstance;

	UCPP_SaveGame* SaveComponent;

	void Jump();
	void Interact();
	void SavePosition();
	void LoadPosition();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Rate);
	void LookUp(float Rate);
	virtual void BeginPlay() override;

private:
	float ForwardInput;
	float RightInput;
};
