// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CMS.h"
#include "Store/UnitStore.h"

class UCMS const* GetCMS();
class UUnitStore const& GetUnitStore();
class AColosseumHUD const* GetHUD(UWorld const* InWorld);
class UWorldHudWidget const* GetWorldWidget(UWorld const* InWorld);