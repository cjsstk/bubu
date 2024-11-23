// Fill out your copyright notice in the Description page of Project Settings.


#include "ColosseumGameInstance.h"

void UColosseumGameInstance::Init()
{
	Super::Init();

	UnitStore = NewObject<UUnitStore>(this);
	UnitStore->InitStore();
}

void UColosseumGameInstance::Shutdown()
{
	UnitStore->Shutdown();

	Super::Shutdown();
}
