// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionStates.h"
#include "ActionFSM.generated.h"


/**
 * 
 */
UCLASS()
class COLOSSEUM_API UActionFSM : public UObject
{
	 GENERATED_BODY()

public:
	UActionFSM();

	//typedef void (A::* CallBackFunction)(void);

	void InitFSM(ACharacter* InOwner, int32 InWeaponType);
	void TickFSM(float DeltaTime);

	//void AddState(EFSMActionType const& InType, CallBackFunction OnEnter);
	void AddState(EFSMActionType const& InType, class UActionState* InActionState, bool bIsDefault = false);
	void AddTranslation(EFSMActionType const& InStart, EFSMActionType const& InEnd);
	bool ChangeState(EFSMActionType const& InNewState, EFSMActionType const& InFinishState = EFSMActionType::Idle, bool bInExecuteEvent = true, FActionParams const& InParams = FActionParams());

	EFSMActionType GetCurrentState() const { return CurrentState ? CurrentState->GetActionType() : EFSMActionType::Idle; }

private:
	UPROPERTY()
	TMap<EFSMActionType, class UActionState*> ActionStates;

	UPROPERTY()
	class UActionState* CurrentState;

	UPROPERTY()
	FActionParams CurrentParams;

	UPROPERTY()
	class ACharacter* Owner = nullptr;

	const FCharacterAnimMontageRow* AnimRow = nullptr;
	TMap<EFSMActionType, TArray<EFSMActionType>> Traslations;

};
