// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common/ColosseumAction.h"
#include "StoreBaseWidget.generated.h"

#define RegisterStoreAction(ActionType, Function) \
	Subscribe(ActionType); \
	GetActionDelegate(ActionType).BindUObject(this, Function);

DECLARE_DELEGATE_OneParam(FOnActionDelegate, const TSharedPtr<FStoreAction>&)

/**
 *
 */
UCLASS()
class COLOSSEUM_API UStoreBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void OnStoreAction(const TSharedPtr<FStoreAction>& Action);

protected:
	void Subscribe(const EActionType& InActionType);
	FOnActionDelegate& GetActionDelegate(EActionType InActionType) { return ActionDelegates.FindOrAdd(InActionType); }

private:
	TMap<EActionType, FOnActionDelegate> ActionDelegates;

};
