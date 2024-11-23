// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "ColosseumCharacter.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	bool bRun = RunBehaviorTree(EnemyBT.LoadSynchronous());
	if (!bRun)
	{
		ensure(0);
	}

}

bool AEnemyAIController::FindTarget()
{
	TArray<AActor*> Found;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AColosseumCharacter::StaticClass(), Found);

	if (Found.IsEmpty())
	{
		ensure(0);
		return false;
	}

	GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"), Found[0]);

	return true;
}
