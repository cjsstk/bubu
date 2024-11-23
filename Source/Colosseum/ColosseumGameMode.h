// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Common\CMS.h"
#include "ColosseumGameMode.generated.h"

UCLASS(minimalapi)
class AColosseumGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AColosseumGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

private:
	UPROPERTY()
	class UCMS* CMS = nullptr;

};



