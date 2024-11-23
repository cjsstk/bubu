// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/ActionFSM.h"
#include "ColosseumCore.h"
#include "ColosseumCharacter.h"
#include "EnemyCharacter.h"

UActionFSM::UActionFSM()
{
	ActionStates.Reset();
	Traslations.Reset();
}

void UActionFSM::InitFSM(ACharacter* InOwner, int32 InWeaponType)
{
	if (!InOwner)
	{
		ensure(0);
		return;
	}

	ActionStates.Reset();
	Traslations.Reset();

	AnimRow = GetCMS()->GetCharacterAnimRow(InWeaponType);
	check(AnimRow);

	Owner = InOwner;

}

void UActionFSM::TickFSM(float DeltaTime)
{
	if (CurrentState)
	{
		CurrentState->OnTickState(DeltaTime);
	}
}

void UActionFSM::AddState(EFSMActionType const& InType, UActionState* InActionState, bool bIsDefault)
{
	if (!InActionState)
	{
		return;
	}

	if (ActionStates.Contains(InType))
	{
		
		return;
	}

	InActionState->SetOwner(Owner);
	InActionState->SetActionType(InType);
	InActionState->SetActionAnim(*AnimRow);
	ActionStates.Add(InType, InActionState);

	if (bIsDefault)
	{
		CurrentState = InActionState;
	}
}

void UActionFSM::AddTranslation(EFSMActionType const& InStart, EFSMActionType const& InEnd)
{
	TArray<EFSMActionType>& Found = Traslations.FindOrAdd(InStart);
	Found.Add(InEnd);
}

bool UActionFSM::ChangeState(EFSMActionType const& InNewState, EFSMActionType const& InFinishState, bool bInExecuteEvent, FActionParams const& InParams)
{
	UActionState** Found = ActionStates.Find(InNewState);
	if (!Found)
	{
		ensure(0);
		return false;
	}

	if (!Traslations[CurrentState->GetActionType()].Contains(InNewState))
	{
		return false;
	}
	
	//UE_LOG(LogTemp, Log, TEXT("Current Montage : %d"), (*Found)->GetActionType());

	UAnimMontage* CurrentMontage = Owner->GetCurrentMontage();
	if (CurrentMontage != nullptr && (*Found)->GetActionAnims().Contains(CurrentMontage))
	{
		return false;
	}

	/*if (Owner->GetMesh()->GetAnimInstance()->IsAnyMontagePlaying())
	{
		return false;
	}*/

	Owner->StopAnimMontage();

	//UE_LOG(LogTemp, Log, TEXT("Change State: %d to %d"), CurrentState->GetActionType(), InNewState);

	if (bInExecuteEvent)
	{
		if (CurrentState)
		{
			CurrentState->OnExitState();
		}

		(*Found)->SetActionParams(InParams);
		(*Found)->OnEnterState(InFinishState);
	}

	CurrentState = *Found;
	CurrentParams = InParams;

	return true;
}

