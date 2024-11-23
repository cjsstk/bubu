// Copyright Epic Games, Inc. All Rights Reserved.

#include "ColosseumCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"


static TAutoConsoleVariable<float> CVarFocusRange
(
	TEXT("co.FocusRange"),
	1000.f,
	TEXT("Can Focus Enemy Range."),
	ECVF_Cheat
);


//////////////////////////////////////////////////////////////////////////
// AColosseumCharacter

AColosseumCharacter::AColosseumCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	//GetCharacterMovement()->JumpZVelocity = 700.f;
	//GetCharacterMovement()->AirControl = 0.35f;
	//GetCharacterMovement()->MaxWalkSpeed = 500.f;
	//GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	//GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	ActionComponent = CreateDefaultSubobject<UCharacterActionComponent>(TEXT("ActionComp"));

}

bool AColosseumCharacter::IsComboTiming() const
{
	return ActionComponent->IsComboTiming();
}

EFSMActionType AColosseumCharacter::GetCurrentFSMState() const
{
	return ActionComponent->GetCurrentState();
}

void AColosseumCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AColosseumCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsFocusing)
	{
		if (Controller != nullptr)
		{
			FVector LookVector = FocusTarget.Get()->GetActorLocation() - GetActorLocation();

			FQuat NewConQuat = FQuat::Slerp(Controller->GetControlRotation().Quaternion(), FRotator(0, LookVector.Rotation().Yaw, 0).Quaternion(), 0.1f);
			FRotator NewConRot = NewConQuat.Rotator();
			NewConRot.Roll = 0.f;

			FRotator NewCamRot = FMath::LerpRange(CameraBoom->GetComponentRotation(), FRotator(LookVector.Rotation().Pitch, 0, 0), 0.5f);
			NewCamRot.Pitch = 0.f;

			//UE_LOG(LogTemp, Log, TEXT("ConRot: %.2f, %.2f, %.2f"), NewConRot.Yaw, NewConRot.Pitch, NewConRot.Roll);
			//UE_LOG(LogTemp, Log, TEXT("CamRot: %.2f, %.2f, %.2f"), NewCamRot.Yaw, NewCamRot.Pitch, NewCamRot.Roll);

			Controller->SetControlRotation(NewConRot);
			CameraBoom->SetWorldRotation(NewCamRot);
		}
	}

	CameraBoom->SetRelativeLocation(FMath::Lerp(CameraBoom->GetRelativeLocation(), bIsFocusing ? FocusCameraHeight : DefaultCameraHeight, 0.1f));

	if (GetMovementComponent()->Velocity.IsNearlyZero())
	{
		ForwadInputValue = 0.f;
		RightInputValue = 0.f;
	}
}

void AColosseumCharacter::OnDamaged(AActor* Attacker, EDamageType DamageType, bool bFromSweep, const FHitResult& SweepResult, const FActionParams& Params)
{
	Super::OnDamaged(Attacker, DamageType, bFromSweep, SweepResult, Params);

	switch (DamageType)
	{
	case EDamageType::Weak:
		ActionComponent->WeakHit(Params);
		break;
	case EDamageType::Strong:
		ActionComponent->StrongHit(Params);
		break;
	case EDamageType::Max:
	default:
		ensure(0);
		break;
	}

}

//////////////////////////////////////////////////////////////////////////
// Input

void AColosseumCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{	
		EnhancedInputComponent->BindAction(InputActions[EInputActionType::Dodge], ETriggerEvent::Triggered, this, &AColosseumCharacter::Dodge);
		EnhancedInputComponent->BindAction(InputActions[EInputActionType::BlockStarted], ETriggerEvent::Triggered, this, &AColosseumCharacter::BlockStarted);
		EnhancedInputComponent->BindAction(InputActions[EInputActionType::BlockFinished], ETriggerEvent::Triggered, this, &AColosseumCharacter::BlockFinished);
		EnhancedInputComponent->BindAction(InputActions[EInputActionType::Combo], ETriggerEvent::Triggered, this, &AColosseumCharacter::Combo);
		EnhancedInputComponent->BindAction(InputActions[EInputActionType::Smash], ETriggerEvent::Triggered, this, &AColosseumCharacter::Smash);

		EnhancedInputComponent->BindAction(InputActions[EInputActionType::Move], ETriggerEvent::Triggered, this, &AColosseumCharacter::Move);
		EnhancedInputComponent->BindAction(InputActions[EInputActionType::Look], ETriggerEvent::Triggered, this, &AColosseumCharacter::Look);

		EnhancedInputComponent->BindAction(InputActions[EInputActionType::Focus], ETriggerEvent::Completed, this, &AColosseumCharacter::Focus);
	}

}

void AColosseumCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	MovementVector = MovementVector.GetSafeNormal();

	ForwadInputValue = MovementVector.Y;
	RightInputValue = MovementVector.X;

	if (ActionComponent->IsActionBlock())
	{
		return;
	}

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AColosseumCharacter::Look(const FInputActionValue& Value)
{
	if (IsFocusing())
	{
		return;
	}

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AColosseumCharacter::Focus(const FInputActionValue& Value)
{
	SetFocusMode(!bIsFocusing);
}

void AColosseumCharacter::Dodge(const FInputActionValue& Value)
{
	ActionComponent->Dodge();
}

void AColosseumCharacter::BlockStarted(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Block Started"));
	ActionComponent->BlockStarted();
}

void AColosseumCharacter::BlockFinished(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Block Finished"));
	ActionComponent->BlockFinished();
}

void AColosseumCharacter::Combo(const FInputActionValue& Value)
{
	ActionComponent->Combo();
}

void AColosseumCharacter::Smash(const FInputActionValue& Value)
{
	ActionComponent->Smash();
}

bool AColosseumCharacter::SetFocusMode(bool bInIsFocusing)
{
	FocusTarget = nullptr;

	if (bInIsFocusing)
	{
		TArray<AActor*> FoundEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundEnemies);
		
		AEnemyCharacter* TargetCandidate = nullptr;
		float MinDisSqr = MAX_FLT;
		float RangeSqr = FMath::Square(CVarFocusRange.GetValueOnGameThread());

		for (auto const& Found : FoundEnemies)
		{
			if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Found))
			{
				float DistSqr = FVector::DistSquared(GetActorLocation(), Enemy->GetActorLocation());
				if (DistSqr > RangeSqr)
				{
					continue;
				}

				if (DistSqr < MinDisSqr)
				{
					TargetCandidate = Enemy;
				}
			}
		}

		FocusTarget = TargetCandidate;
	}

	bIsFocusing = FocusTarget.IsValid();

	BP_SetFocusMode(bIsFocusing);

	return bIsFocusing;
}




