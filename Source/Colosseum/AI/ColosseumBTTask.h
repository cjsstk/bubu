// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "ColosseumEnum.h"
#include "ColosseumBTTask.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UPlayMontageTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UAnimMontage> Montage;

};

UCLASS()
class COLOSSEUM_API UWalkToTask : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

};

UCLASS()
class COLOSSEUM_API URunToTask : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

};

UCLASS()
class COLOSSEUM_API UAttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UAttackTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly)
	EFSMActionType AttackType = EFSMActionType::Attack1;

};

UCLASS()
class COLOSSEUM_API USmallAttackTask : public UAttackTask
{
	GENERATED_BODY()

public:
	//USmallAttackTask();

	//virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

};