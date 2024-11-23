// Fill out your copyright notice in the Description page of Project Settings.


#include "ColosseumCore.h"

UCMS const* GetCMS()
{
	return UCMS::GetInstance();
}

UUnitStore const& GetUnitStore()
{
	return *UUnitStore::Get();
}

AColosseumHUD const* GetHUD(UWorld const* InWorld)
{
	return Cast<AColosseumHUD>(InWorld->GetFirstPlayerController()->GetHUD());
}

UWorldHudWidget const* GetWorldWidget(UWorld const* InWorld)
{
	return nullptr;
}
