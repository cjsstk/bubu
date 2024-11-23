// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ActionComponent.h"
#include "ColosseumCharacter.h"
#include "ColosseumCore.h"
#include "Common/ActionFSM.h"
#include "EnemyCharacter.h"

UActionComponent::UActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	//ActionFSM = CreateDefaultSubobject<UActionFSM>(TEXT("FSM"));
}

bool UActionComponent::ChangeState(EFSMActionType const& InNewState, EFSMActionType const& InFinishState, bool bInExecuteEvent)
{
	return ActionFSM->ChangeState(InNewState, InFinishState, bInExecuteEvent);
}

EFSMActionType UActionComponent::GetCurrentState() const
{
	return ActionFSM ? ActionFSM->GetCurrentState() : EFSMActionType::Idle;
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ActionFSM = NewObject<UActionFSM>();
	ActionFSM->InitFSM(Cast<ACharacter>(GetOwner()), WeaponType);
}

void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActionFSM->TickFSM(DeltaTime);
}

UAnimInstance* UActionComponent::GetAnimInstance()
{
	if (auto* Character = Cast<ACharacter>(GetOwner()))
	{
		return Character->GetMesh()->GetAnimInstance();
	}

	return nullptr;
}


// UCharacterActionComponent
void UCharacterActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ActionFSM->AddState(EFSMActionType::Idle, NewObject<UIdleState>(), true);
	ActionFSM->AddState(EFSMActionType::Dodge, NewObject<UDodgeState>());
	ActionFSM->AddState(EFSMActionType::Block, NewObject<UBlockState>());
	ActionFSM->AddState(EFSMActionType::Combo, NewObject<UComboState>());
	ActionFSM->AddState(EFSMActionType::Smash, NewObject<USmashState>());
	ActionFSM->AddState(EFSMActionType::WeakHit, NewObject<UWeakHitState>());
	ActionFSM->AddState(EFSMActionType::StrongHit, NewObject<UStrongHitState>());

	ActionFSM->AddTranslation(EFSMActionType::Idle, EFSMActionType::Dodge);
	ActionFSM->AddTranslation(EFSMActionType::Idle, EFSMActionType::Block);
	ActionFSM->AddTranslation(EFSMActionType::Idle, EFSMActionType::Combo);
	ActionFSM->AddTranslation(EFSMActionType::Idle, EFSMActionType::Smash);
	ActionFSM->AddTranslation(EFSMActionType::Idle, EFSMActionType::WeakHit);
	ActionFSM->AddTranslation(EFSMActionType::Idle, EFSMActionType::StrongHit);

	ActionFSM->AddTranslation(EFSMActionType::Dodge, EFSMActionType::Idle);

	ActionFSM->AddTranslation(EFSMActionType::Block, EFSMActionType::Idle);
	ActionFSM->AddTranslation(EFSMActionType::Block, EFSMActionType::Dodge);

	ActionFSM->AddTranslation(EFSMActionType::Combo, EFSMActionType::Idle);
	ActionFSM->AddTranslation(EFSMActionType::Combo, EFSMActionType::Dodge);
	ActionFSM->AddTranslation(EFSMActionType::Combo, EFSMActionType::WeakHit);
	ActionFSM->AddTranslation(EFSMActionType::Combo, EFSMActionType::StrongHit);

	ActionFSM->AddTranslation(EFSMActionType::Smash, EFSMActionType::Idle);
	ActionFSM->AddTranslation(EFSMActionType::Smash, EFSMActionType::Dodge);
	ActionFSM->AddTranslation(EFSMActionType::Smash, EFSMActionType::WeakHit);
	ActionFSM->AddTranslation(EFSMActionType::Smash, EFSMActionType::StrongHit);

	ActionFSM->AddTranslation(EFSMActionType::WeakHit, EFSMActionType::Idle);

	ActionFSM->AddTranslation(EFSMActionType::StrongHit, EFSMActionType::Idle);

	//
	//ActionFSM->ChangeState(EFSMActionType::Idle, EFSMActionType::Idle, false);
}

void UCharacterActionComponent::BlockStarted()
{
	if (IsActionBlock())
	{
		return;
	}

	ActionFSM->ChangeState(EFSMActionType::Block);
}

void UCharacterActionComponent::BlockFinished()
{
	if (GetCurrentState() == EFSMActionType::Block)
	{
		ActionFSM->ChangeState(EFSMActionType::Idle);
	}
}

void UCharacterActionComponent::Dodge()
{
	if (IsActionBlock())
	{
		return;
	}

	if (GetCurrentState() == EFSMActionType::Dodge)
	{
		return;
	}

	ActionFSM->ChangeState(EFSMActionType::Dodge);
}

void UCharacterActionComponent::Combo()
{
	if (IsActionBlock())
	{
		return;
	}

	if (GetCurrentState() == EFSMActionType::Idle)
	{
		CurrentComboCount = 0;
		bIsReadyNextCombo = false;
		ActionFSM->ChangeState(EFSMActionType::Combo);
	}
	else if (GetCurrentState() == EFSMActionType::Combo)
	{
		if (!IsComboTiming())
		{
			return;
		}

		bIsReadyNextCombo = true;
	}
}

void UCharacterActionComponent::Smash()
{
	if (IsActionBlock())
	{
		return;
	}

	if (GetCurrentState() == EFSMActionType::Idle)
	{
		CurrentComboCount = 0;
		bIsReadyNextCombo = false;
		ActionFSM->ChangeState(EFSMActionType::Smash);
	}
	else if (GetCurrentState() == EFSMActionType::Smash)
	{
		if (!IsComboTiming())
		{
			return;
		}

		bIsReadyNextCombo = true;
	}
}

void UCharacterActionComponent::WeakHit(FActionParams const& InParams)
{
	ActionFSM->ChangeState(EFSMActionType::WeakHit, EFSMActionType::Idle, true, InParams);
}

void UCharacterActionComponent::StrongHit(FActionParams const& InParams)
{
	ActionFSM->ChangeState(EFSMActionType::StrongHit, EFSMActionType::Idle, true, InParams);
}

void UCharacterActionComponent::GoNextCombo(int32 InComboNum)
{
	if (InComboNum == CurrentComboCount)
	{
		return;
	}

	CurrentComboCount = InComboNum;
	bIsReadyNextCombo = false;

	FString SectionName = FString::Printf(TEXT("Combo%d"), CurrentComboCount);

	GetAnimInstance()->Montage_JumpToSection(FName(*SectionName));
}

class AColosseumCharacter* UCharacterActionComponent::GetCharacter()
{
	return Cast<AColosseumCharacter>(GetOwner());
}


//
void UEnemyActionComponent::Attack1()
{
	ActionFSM->ChangeState(EFSMActionType::Attack1);
}

void UEnemyActionComponent::Combo()
{
}

void UEnemyActionComponent::Smash()
{
}

void UEnemyActionComponent::Execution()
{
}

void UEnemyActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ActionFSM->AddState(EFSMActionType::Idle, NewObject<UIdleState>(), true);
	ActionFSM->AddState(EFSMActionType::Attack1, NewObject<UAttack1State>());

	ActionFSM->AddTranslation(EFSMActionType::Idle, EFSMActionType::Attack1);

	ActionFSM->AddTranslation(EFSMActionType::Attack1, EFSMActionType::Idle);
}

AEnemyCharacter* UEnemyActionComponent::GetEnemyCharacter()
{
	return Cast<AEnemyCharacter>(GetOwner());
}
