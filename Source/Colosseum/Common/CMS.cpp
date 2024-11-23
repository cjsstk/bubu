// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/CMS.h"
#include "UObject/ConstructorHelpers.h"

UCMS* UCMS::Singleton = nullptr;

UCMS::UCMS()
{
	UCMS::Singleton = this;
}

void UCMS::LoadTable()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAnimDT(TEXT("/Game/DataTable/CharacterAnimDataTable"));
	if (CharacterAnimDT.Succeeded())
	{
		CharacterAnimTable = CharacterAnimDT.Object;
	}

}

FCharacterAnimMontageRow const* UCMS::GetCharacterAnimRow(int32 InKey) const
{
	return CharacterAnimTable->FindRow<FCharacterAnimMontageRow>(FName(*FString::FromInt(InKey)), FString(""));
}
