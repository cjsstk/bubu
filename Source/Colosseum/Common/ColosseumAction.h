// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM()
enum class EActionType : uint16
{
	PlayerHpChanged,
	EnemyHpChanged,
};

//
struct FStoreAction
{
	explicit FStoreAction(EActionType InActionType) : ActionType(InActionType) {}

	virtual ~FStoreAction() {}

	EActionType GetActionType() const { return ActionType; }

protected:
	EActionType ActionType;

};

template<class T>
struct FStoreActionOneParam : public FStoreAction
{
	explicit FStoreActionOneParam(EActionType InActionType, const T& InVal) : FStoreAction(InActionType), Val(InVal) {}

	const T& GetVal() const { return Val; }

protected:
	T Val;
};

template<class T, class U>
struct FStoreActionTwoParams : public FStoreActionOneParam<T>
{
	explicit FStoreActionTwoParams(EActionType InActionType, const T& InVal, const U& InVal2) : FStoreActionOneParam<T>(InActionType, InVal), Val2(InVal2) {}

	const U& GetVal2() const { return Val2; }

protected:
	U Val2;
};


//
DECLARE_DELEGATE_RetVal_OneParam(bool, FOnStoreAction, TSharedPtr<FStoreAction>)
//

class COLOSSEUM_API Action
{
public:
	static void Dispatch(TSharedPtr<FStoreAction> Action);
};

// Action Dispatch
#define ACTION_DISPATCH(ActionType) \
	Action::Dispatch(MakeShared<FStoreAction>(EActionType::ActionType))
#define ACTION_DISPATCH_OneParam(ActionType, Type1, Val) \
	Action::Dispatch(MakeShared<FStoreActionOneParam<Type1>>(EActionType::ActionType, Val))
#define ACTION_DISPATCH_TwoParams(ActionType, Type1, Val, Type2, Val2) \
	Action::Dispatch(MakeShared<FStoreActionTwoParams<Type1, Type2>>(EActionType::ActionType, Val, Val2))

// Action Parse
#define ACTION_PARSE_OneParam(Type1, Action) \
	StaticCastSharedPtr<FStoreActionOneParam<Type1>>(Action)
#define ACTION_PARSE_TwoParams(Type1, Type2, Action) \
	StaticCastSharedPtr<FStoreActionTwoParams<Type1, Type2>>(Action)

// Action Handler ---- Store에서 사용.
#define DECLARE_ACTION(ActionType) \
	bool OnStoreAction##ActionType(TSharedPtr<FStoreAction> InAction)
#define DECLARE_ACTION_DEFAULT(ActionType) \
	bool OnStoreAction##ActionType(TSharedPtr<FStoreAction> InAction) { return true; }

#define IMPLEMENT_ACTION(ClassName, ActionType) \
	bool ClassName::OnStoreAction##ActionType(TSharedPtr<FStoreAction> InAction)

#define REGISTER_ACTION(ClassName, ActionType) \
	RegisterActionDelegate(EActionType::ActionType, FOnStoreAction::CreateUObject(this, &ClassName::OnStoreAction##ActionType))