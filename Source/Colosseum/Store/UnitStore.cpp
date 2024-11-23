// Fill out your copyright notice in the Description page of Project Settings.


#include "Store/UnitStore.h"

#include "Widget/StoreBaseWidget.h"

UUnitStore* UUnitStore::Singleton = nullptr;

UUnitStore::UUnitStore()
{
	UUnitStore::Singleton = this;
}

void UUnitStore::InitStore()
{
	if (bIsInit)
	{
		return;
	}

	SubscribeWidgets.Empty();

	REGISTER_ACTION(UUnitStore, PlayerHpChanged);
	REGISTER_ACTION(UUnitStore, EnemyHpChanged);

	bIsInit = true;
}

void UUnitStore::Shutdown()
{
	for (auto& Delegate : ActionDelegate)
	{
		Delegate.Value.Unbind();
	}

	ActionDelegate.Empty();
	SubscribeWidgets.Empty();
}

void UUnitStore::Register(const EActionType& InActionType, UStoreBaseWidget* InWidget)
{
	FSubscribeWidgets& SubsWidgets = SubscribeWidgets.FindOrAdd(InActionType);
	SubsWidgets.Widgets.AddUnique(InWidget);
}

void UUnitStore::Dispatch(TSharedPtr<FStoreAction> Action)
{
	FOnStoreAction* Delegate = ActionDelegate.Find(Action->GetActionType());
	if (!ensure(Delegate))
	{
		// Not registered action type
		return;
	}

	if (!Delegate->Execute(Action))
	{
		return;
	}

	FSubscribeWidgets* Widgets = SubscribeWidgets.Find(Action->GetActionType());
	if (Widgets)
	{
		for (const auto& Widget : Widgets->Widgets)
		{
			if (Widget)
			{
				Widget->OnStoreAction(Action);
			}
		}
	}
}

void UUnitStore::RegisterActionDelegate(EActionType InActionType, const FOnStoreAction& InActionDelegate)
{
	FOnStoreAction& Delegate = ActionDelegate.FindOrAdd(InActionType);
	Delegate = InActionDelegate;
}

IMPLEMENT_ACTION(UUnitStore, PlayerHpChanged)
{
	/*const auto& Action = ACTION_PARSE_AddItem(InAction);
	int32 ItemKey = Action->GetVal();

	AddItem(ItemKey);*/

	return true;
}

IMPLEMENT_ACTION(UUnitStore, EnemyHpChanged)
{
	/*const auto& Action = ACTION_PARSE_AddItem(InAction);
	int32 ItemKey = Action->GetVal();

	AddItem(ItemKey);*/

	return true;
}