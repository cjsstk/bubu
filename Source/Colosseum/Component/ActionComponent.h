// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ColosseumEnum.h"
#include "ColosseumStruct.h"
#include "ActionComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COLOSSEUM_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActionComponent();

	bool ChangeState(EFSMActionType const& InNewState, EFSMActionType const& InFinishState = EFSMActionType::Idle, bool bInExecuteEvent = true);
	EFSMActionType GetCurrentState() const;

	void SetActionBlock(bool bInBlock) { bActionBlock = bInBlock; }
	bool IsActionBlock() const { return bActionBlock; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	class UAnimInstance* GetAnimInstance();

	UPROPERTY()
	class UActionFSM* ActionFSM;

	UPROPERTY(EditAnywhere)
	int32 WeaponType = DEFAULT_WEAPON_TYPE;

	bool bPlayingStrongHitAnimation = false;
	bool bActionBlock = false;

};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COLOSSEUM_API UCharacterActionComponent : public UActionComponent
{
	GENERATED_BODY()

public:
	void BlockStarted();
	void BlockFinished();
	void Dodge();
	void Combo();
	void Smash();
	void WeakHit(FActionParams const& InParams);
	void StrongHit(FActionParams const& InParams);

	void GoNextCombo(int32 InComboNum);

	void SetPlayingBlockAnimation(bool bIsPlaying) { bPlayingBlockAnimation = bIsPlaying; }
	bool IsPlayingBlockAnimation() const { return bPlayingBlockAnimation; }

	void SetComboTiming(bool bInIsTiming) { bIsComboTiming = bInIsTiming; }
	bool IsComboTiming() const { return bIsComboTiming; };
	int32 GetCurrentComboCount() const { return CurrentComboCount; }
	//void SetReadyNextCombo(bool bInReadyNextCombo) { bIsReadyNextCombo = bInReadyNextCombo; }
	bool IsReadyNextCombo() const { return bIsReadyNextCombo; }

protected:
	virtual void BeginPlay() override;


private:
	class AColosseumCharacter* GetCharacter();

	bool bPlayingBlockAnimation = false;
	bool bIsComboTiming = false;
	bool bIsReadyNextCombo = false;
	int32 CurrentComboCount = 0;

};


//
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COLOSSEUM_API UEnemyActionComponent : public UActionComponent
{
	GENERATED_BODY()

public:
	void Attack1();
	void Combo();
	void Smash();
	void Execution();

protected:
	virtual void BeginPlay() override;


private:
	class AEnemyCharacter* GetEnemyCharacter();


};