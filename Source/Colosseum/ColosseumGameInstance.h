// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Store/UnitStore.h"
#include "ColosseumGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UColosseumGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

private:
	UPROPERTY()
	class UUnitStore* UnitStore;

};
