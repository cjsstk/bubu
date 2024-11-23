// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ColosseumHUD.generated.h"

/**
 * 
 */
UCLASS()
class COLOSSEUM_API AColosseumHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	class UWorldHudWidget const& GetWorldHudWidget() const { return *WorldHudWidget; }

protected:
	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UWorldHudWidget> WorldHudWidgetClass;

	UPROPERTY()
	class UWorldHudWidget* WorldHudWidget = nullptr;

};
