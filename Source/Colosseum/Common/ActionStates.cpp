// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/ActionStates.h"
#include "ColosseumCharacter.h"
#include "Component/ActionComponent.h"
#include "EnemyCharacter.h"
#include "GameFramework/Controller.h"
#include "Math/UnrealMathUtility.h"

void UActionState::OnEnterState(EFSMActionType const& InExitState)
{
	//UE_LOG(LogTemp, Log, TEXT("Enter Action State: %d"), ActionType);

	ExitAction = InExitState;

	GetAnimInstance()->OnMontageStarted.AddUniqueDynamic(this, &UActionState::OnMontageStarted);
	GetAnimInstance()->OnMontageEnded.AddUniqueDynamic(this, &UActionState::OnMontageEnded);
}

void UActionState::OnExitState()
{
	//UE_LOG(LogTemp, Log, TEXT("Exit Action State: %d"), ActionType);

	GetAnimInstance()->OnMontageStarted.RemoveAll(this);
	GetAnimInstance()->OnMontageEnded.RemoveAll(this);
}

void UActionState::SetOwner(ACharacter* InOwner)
{
	Owner = InOwner; 

	//GetAnimInstance()->OnMontageStarted.AddUniqueDynamic(this, &UActionState::OnMontageStarted);
	//GetAnimInstance()->OnMontageEnded.AddUniqueDynamic(this, &UActionState::OnMontageEnded);
}

UAnimInstance* UActionState::GetAnimInstance()
{
	return Owner->GetMesh()->GetAnimInstance();
}

void UActionState::OnMontageEnd(UAnimMontage* InMontage, bool bInterrupted)
{
	if (bExitOnAnimFinish)
	{
		if (bInterrupted)
		{
			return;
		}

		//UE_LOG(LogTemp, Log, TEXT("Interrupted: %d"), bInterrupted);

		//AColosseumCharacter* Player = Cast<AColosseumCharacter>(Owner);
		//Owner->StopAnimMontage();

		UActionComponent* ActionComp = Owner->FindComponentByClass<UActionComponent>();
		if (ActionComp)
		{
			ActionComp->ChangeState(ExitAction);
		}
	}
}

void UActionState::OnMontageStarted(UAnimMontage* InMontage)
{
	OnMontageStart(InMontage);
}

void UActionState::OnMontageEnded(UAnimMontage* InMontage, bool bInterrupted)
{
	OnMontageEnd(InMontage, bInterrupted);
}

// UDodgeState
UDodgeState::UDodgeState()
{
	bExitOnAnimFinish = true;
}

void UDodgeState::OnEnterState(EFSMActionType const& InExitState)
{
	Super::OnEnterState(InExitState);

	AColosseumCharacter* Player = Cast<AColosseumCharacter>(Owner);
	if (Player)
	{
		EDodgeDirection Dir = EDodgeDirection::Front;
		float Forward = Player->GetForwardInputValue();
		float Right = Player->GetRightInputValue();

		if (Player->IsFocusing())
		{
			if (!FMath::IsNearlyZero(Forward))
			{
				Dir = Forward > 0.f ? EDodgeDirection::Front : EDodgeDirection::Back;
			}

			if (!FMath::IsNearlyZero(Right))
			{
				Dir = Right > 0.f ? EDodgeDirection::Right : EDodgeDirection::Left;
			}
		}
		else
		{
			FVector RotationDir = FRotationMatrix(Owner->GetControlRotation()).GetScaledAxis(EAxis::X);
			FVector RightVec = FRotationMatrix(Owner->GetControlRotation()).GetScaledAxis(EAxis::Y);

			if (!FMath::IsNearlyZero(Forward))
			{
				RotationDir = Forward > 0.f ? RotationDir : -RotationDir;
			}

			if (!FMath::IsNearlyZero(Right))
			{
				if (FMath::IsNearlyZero(Forward))
				{
					RotationDir = FVector::ZeroVector;
				}

				RotationDir += Right > 0.f ? RightVec : -RightVec;
			}

			RotationDir.Z = 0;

			Owner->SetActorRotation(RotationDir.Rotation());
		}

		Owner->PlayAnimMontage(ActionAnims[(int32)Dir]);
	}
	
}

void UDodgeState::SetActionAnim(FCharacterAnimMontageRow const& InAnimRow)
{
	ActionAnims.Reset((int32)EDodgeDirection::Max);

	for (int32 Index = 0; Index < (int32)EDodgeDirection::Max; ++Index)
	{
		EDodgeDirection Direction = (EDodgeDirection)Index;
		if (!InAnimRow.DodgeAnims.Contains(Direction))
		{
			ActionAnims.Add(nullptr);
			continue;
		}

		ActionAnims.Add(InAnimRow.DodgeAnims[Direction].LoadSynchronous());
	}
}

//
UComboState::UComboState()
{
	bExitOnAnimFinish = true;
}

void UComboState::OnEnterState(EFSMActionType const& InExitState)
{
	Super::OnEnterState(InExitState);

	AColosseumCharacter* Player = Cast<AColosseumCharacter>(Owner);
	if (Player)
	{
		Owner->PlayAnimMontage(ActionAnims[0]);
	}
}

void UComboState::SetActionAnim(FCharacterAnimMontageRow const& InAnimRow)
{
	ActionAnims.Empty();

	if (!InAnimRow.FSMAnims.Contains(EFSMActionType::Combo))
	{
		ensure(0);
		return;
	}

	ActionAnims.Add(InAnimRow.FSMAnims[EFSMActionType::Combo].LoadSynchronous());
}

//
USmashState::USmashState()
{
	bExitOnAnimFinish = true;
}

void USmashState::OnEnterState(EFSMActionType const& InExitState)
{
	Super::OnEnterState(InExitState);

	AColosseumCharacter* Player = Cast<AColosseumCharacter>(Owner);
	if (Player)
	{
		Owner->PlayAnimMontage(ActionAnims[0]);
	}
}

void USmashState::SetActionAnim(FCharacterAnimMontageRow const& InAnimRow)
{
	ActionAnims.Empty();

	if (!InAnimRow.FSMAnims.Contains(EFSMActionType::Smash))
	{
		ensure(0);
		return;
	}

	ActionAnims.Add(InAnimRow.FSMAnims[EFSMActionType::Smash].LoadSynchronous());
}

//
UAttack1State::UAttack1State()
{
	bExitOnAnimFinish = true;
}

void UAttack1State::OnEnterState(EFSMActionType const& InExitState)
{
	Super::OnEnterState(InExitState);

	AEnemyCharacter* Player = Cast<AEnemyCharacter>(Owner);
	if (Player)
	{
		Owner->PlayAnimMontage(ActionAnims[0]);
	}
}

void UAttack1State::SetActionAnim(FCharacterAnimMontageRow const& InAnimRow)
{
	ActionAnims.Empty();

	if (!InAnimRow.FSMAnims.Contains(EFSMActionType::Attack1))
	{
		ensure(0);
		return;
	}

	ActionAnims.Add(InAnimRow.FSMAnims[EFSMActionType::Attack1].LoadSynchronous());
}

//
UWeakHitState::UWeakHitState()
{
	bExitOnAnimFinish = true;
}

void UWeakHitState::OnEnterState(EFSMActionType const& InExitState)
{
	Super::OnEnterState(InExitState);

	ABaseCharacter* Character = Cast<ABaseCharacter>(Owner);
	if (Character)
	{
		Owner->PlayAnimMontage(ActionAnims[ActionParams.bFrontDamage ? (int32)EDodgeDirection::Front : (int32)EDodgeDirection::Back]);
	}
}

void UWeakHitState::SetActionAnim(FCharacterAnimMontageRow const& InAnimRow)
{
	ActionAnims.Empty();

	if (InAnimRow.WeakHitAnims.Num() <= 0)
	{
		ensure(0);
		return;
	}

	for (int32 Index = 0; Index < (int32)EDodgeDirection::Max; ++Index)
	{
		EDodgeDirection Direction = (EDodgeDirection)Index;
		if (!InAnimRow.WeakHitAnims.Contains(Direction))
		{
			ActionAnims.Add(nullptr);
			continue;
		}

		ActionAnims.Add(InAnimRow.WeakHitAnims[Direction].LoadSynchronous());
	}

}

//
UStrongHitState::UStrongHitState()
{
	bExitOnAnimFinish = true;
}

void UStrongHitState::OnEnterState(EFSMActionType const& InExitState)
{
	Super::OnEnterState(InExitState);

	ABaseCharacter* Character = Cast<ABaseCharacter>(Owner);
	if (Character)
	{
		Owner->PlayAnimMontage(ActionAnims[ActionParams.bFrontDamage ? (int32)EDodgeDirection::Front : (int32)EDodgeDirection::Back]);
	}
}

void UStrongHitState::SetActionAnim(FCharacterAnimMontageRow const& InAnimRow)
{
	ActionAnims.Empty();

	if (InAnimRow.StrongHitAnims.Num() <= 0)
	{
		ensure(0);
		return;
	}

	for (int32 Index = 0; Index < (int32)EDodgeDirection::Max; ++Index)
	{
		EDodgeDirection Direction = (EDodgeDirection)Index;
		if (!InAnimRow.StrongHitAnims.Contains(Direction))
		{
			ActionAnims.Add(nullptr);
			continue;
		}

		ActionAnims.Add(InAnimRow.StrongHitAnims[Direction].LoadSynchronous());
	}

}