// Copyright Epic Games, Inc. All Rights Reserved.

#include "ColosseumGameMode.h"
#include "ColosseumCharacter.h"
#include "UObject/ConstructorHelpers.h"

AColosseumGameMode::AColosseumGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
	
	CMS = NewObject<UCMS>();
	CMS->LoadTable();
}

void AColosseumGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);


}
