// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/StoreBaseWidget.h"
#include "ColosseumCore.h"

void UStoreBaseWidget::OnStoreAction(const TSharedPtr<FStoreAction>& Action)
{
	FOnActionDelegate* Delegate = ActionDelegates.Find(Action->GetActionType());
	if (Delegate)
	{
		Delegate->ExecuteIfBound(Action);
	}
}

void UStoreBaseWidget::Subscribe(const EActionType& InActionType)
{
	UUnitStore::Get()->Register(InActionType, this);
}
