// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;
	//virtual void OnUnPossess() override;

	bool FindTarget();

private:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UBehaviorTree> EnemyBT;


};
