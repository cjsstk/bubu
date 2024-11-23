// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ColosseumBTTask.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ColosseumCharacter.h"
#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UPlayMontageTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* Character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character)
	{
		return EBTNodeResult::Failed;
	}

	float Length = Character->PlayAnimMontage(Montage.LoadSynchronous());

	return Length > 0.f ? EBTNodeResult::InProgress : EBTNodeResult::Failed;
}

//
EBTNodeResult::Type UWalkToTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* Character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character)
	{
		return EBTNodeResult::Failed;
	}

	Character->GetCharacterMovement()->MaxWalkSpeed = 200.f;

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

//
EBTNodeResult::Type URunToTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* Character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character)
	{
		return EBTNodeResult::Failed;
	}

	Character->GetCharacterMovement()->MaxWalkSpeed = 500.f;

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

//
UAttackTask::UAttackTask()
{
	bNotifyTick = true;
	bNotifyTaskFinished = false;
	bIgnoreRestartSelf = false;
	bTickIntervals = false;
}

EBTNodeResult::Type UAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character)
	{
		return EBTNodeResult::Failed;
	}

	if (!Character->ChangeState(AttackType))
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UAttackTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AEnemyCharacter* Character = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Character)
	{
		return;
	}

	if (Character->GetCurrentFSMState() == EFSMActionType::Idle)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}



