// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ColosseumEnum.h"
#include "ColosseumStruct.h"
#include "CMS.h"
#include "ActionStates.generated.h"


UCLASS()
class COLOSSEUM_API UActionState : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnEnterState(EFSMActionType const& InExitState = EFSMActionType::Idle);
	virtual void OnTickState(float DeltaTime) {}
	virtual void OnExitState();

	virtual void SetActionAnim(FCharacterAnimMontageRow const& InAnimRow) {}

	void SetOwner(ACharacter* InOwner);
	void SetActionType(EFSMActionType const& InType) { ActionType = InType; }
	void SetActionParams(FActionParams const& InParams) { ActionParams = InParams; }

	TArray<class UAnimMontage*> const& GetActionAnims() { return ActionAnims; }
	EFSMActionType const& GetActionType() const { return ActionType; }
	class UAnimInstance* GetAnimInstance();

protected:
	virtual void OnMontageStart(UAnimMontage* InMontage) {}
	virtual void OnMontageEnd(UAnimMontage* InMontage, bool bInterrupted);

protected:
	UFUNCTION()
	void OnMontageStarted(UAnimMontage* InMontage);

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* InMontage, bool bInterrupted);

	UPROPERTY()
	class ACharacter* Owner = nullptr;

	UPROPERTY()
	TArray<class UAnimMontage*> ActionAnims;

	UPROPERTY()
	FActionParams ActionParams;

	EFSMActionType ActionType = EFSMActionType::Idle;
	EFSMActionType ExitAction = EFSMActionType::Idle;

	bool bExitOnAnimFinish = false;
};


UCLASS()
class COLOSSEUM_API UIdleState : public UActionState
{
	GENERATED_BODY()

public:
	//virtual void OnEnterState(EFSMActionType const& InFinishState) override;
	//virtual void OnTickState(float DeltaTime) override;
	//virtual void OnExitState() override;


private:

};


UCLASS()
class COLOSSEUM_API UBlockState : public UActionState
{
	GENERATED_BODY()

public:
	//virtual void OnEnterState(EFSMActionType const& InExitState) override;
	//virtual void OnTickState(float DeltaTime) override;
	//virtual void OnExitState() override;


private:

};

UCLASS()
class COLOSSEUM_API UDodgeState : public UActionState
{
	GENERATED_BODY()

public:
	UDodgeState();

	virtual void OnEnterState(EFSMActionType const& InExitState) override;
	//virtual void OnTickState(float DeltaTime) override;
	//virtual void OnExitState() override;

	virtual void SetActionAnim(FCharacterAnimMontageRow const& InAnimRow) override;

private:
	
};


UCLASS()
class COLOSSEUM_API UComboState : public UActionState
{
	GENERATED_BODY()

public:
	UComboState();

	virtual void OnEnterState(EFSMActionType const& InExitState) override;
	//virtual void OnTickState(float DeltaTime) override;
	//virtual void OnExitState() override;

	virtual void SetActionAnim(FCharacterAnimMontageRow const& InAnimRow) override;

private:

};


UCLASS()
class COLOSSEUM_API USmashState : public UActionState
{
	GENERATED_BODY()

public:
	USmashState();

	virtual void OnEnterState(EFSMActionType const& InExitState) override;
	//virtual void OnTickState(float DeltaTime) override;
	//virtual void OnExitState() override;

	virtual void SetActionAnim(FCharacterAnimMontageRow const& InAnimRow) override;

private:

};

//
UCLASS()
class COLOSSEUM_API UAttack1State : public UActionState
{
	GENERATED_BODY()

public:
	UAttack1State();

	virtual void OnEnterState(EFSMActionType const& InExitState) override;
	virtual void SetActionAnim(FCharacterAnimMontageRow const& InAnimRow) override;

private:

};

//
UCLASS()
class COLOSSEUM_API UWeakHitState : public UActionState
{
	GENERATED_BODY()

public:
	UWeakHitState();

	virtual void OnEnterState(EFSMActionType const& InExitState) override;
	virtual void SetActionAnim(FCharacterAnimMontageRow const& InAnimRow) override;

private:

};

//
UCLASS()
class COLOSSEUM_API UStrongHitState : public UActionState
{
	GENERATED_BODY()

public:
	UStrongHitState();

	virtual void OnEnterState(EFSMActionType const& InExitState) override;
	virtual void SetActionAnim(FCharacterAnimMontageRow const& InAnimRow) override;

private:

};