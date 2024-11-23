// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Common/ColosseumAction.h"
#include "UnitStore.generated.h"


USTRUCT()
struct FSubscribeWidgets
{
	GENERATED_BODY()

public:
	TArray<class UStoreBaseWidget*> Widgets;

};

/**
 *
 */
UCLASS()
class COLOSSEUM_API UUnitStore : public UObject
{
	GENERATED_BODY()

public:
	friend class Action;
	friend class UStoreBaseWidget;

	UUnitStore();

	void InitStore();
	void Shutdown();
	void Register(const EActionType& InActionType, class UStoreBaseWidget* InWidget);

	void SetWorld(class UWorld* NewWorld) { World = NewWorld; }

	//----------
	static UUnitStore* Get() { return Singleton; }
private:
	static UUnitStore* Singleton;

	void Dispatch(TSharedPtr<FStoreAction> Action);
	void RegisterActionDelegate(EActionType InActionType, const FOnStoreAction& InActionDelegate);

	struct FActionDelegate
	{
		TArray<FOnStoreAction> OnActions;
	};

	TMap<EActionType, FOnStoreAction> ActionDelegate;
	TMap<EActionType, FSubscribeWidgets> SubscribeWidgets;

private:
	DECLARE_ACTION(PlayerHpChanged);
	DECLARE_ACTION(EnemyHpChanged);

private:
	UPROPERTY()
	class UWorld* World;

	bool bIsInit = false;
	bool bLoaded = false;
};
