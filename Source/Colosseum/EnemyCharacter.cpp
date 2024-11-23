// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "AI/EnemyAIController.h"
#include "Component/DamageCapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ActionComponent = CreateDefaultSubobject<UEnemyActionComponent>(TEXT("ActionComp"));
}

bool AEnemyCharacter::SmallAttack()
{
	return ActionComponent->ChangeState(EFSMActionType::Attack1);
}

bool AEnemyCharacter::ChangeState(EFSMActionType const& ActionType)
{
	return ActionComponent->ChangeState(ActionType);
}

EFSMActionType AEnemyCharacter::GetCurrentFSMState() const
{
	return ActionComponent->GetCurrentState();
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AEnemyAIController* AIController = Cast<AEnemyAIController>(GetController()))
	{
		AIController->FindTarget();
	}
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

