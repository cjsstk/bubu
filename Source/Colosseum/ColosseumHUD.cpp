// Fill out your copyright notice in the Description page of Project Settings.


#include "ColosseumHUD.h"
#include "Blueprint/UserWidget.h"
#include "Widget/WorldHudWidget.h"

void AColosseumHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(WorldHudWidgetClass))
	{
		WorldHudWidget = CreateWidget<UWorldHudWidget>(GetWorld(), WorldHudWidgetClass.Get());
		WorldHudWidget->AddToViewport();
		
	}
}
