// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "ColosseumEnum.h"
#include "Component/ActionComponent.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class COLOSSEUM_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	bool SmallAttack();
	
	bool ChangeState(EFSMActionType const& ActionType);

	EFSMActionType GetCurrentFSMState() const;

	class UEnemyActionComponent* GetActionComponent() const { return ActionComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UEnemyActionComponent* ActionComponent;

};
