// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ColosseumEnum.h"
#include "CMS.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAnimMontageRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EFSMActionType, TSoftObjectPtr<class UAnimMontage>> FSMAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EDodgeDirection, TSoftObjectPtr<class UAnimMontage>> DodgeAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EDodgeDirection, TSoftObjectPtr<class UAnimMontage>> WeakHitAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EDodgeDirection, TSoftObjectPtr<class UAnimMontage>> StrongHitAnims;

};

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UCMS : public UObject
{
	GENERATED_BODY()
	
public:
	UCMS();

	static UCMS* GetInstance() { return Singleton; }

	void LoadTable();

	FCharacterAnimMontageRow const* GetCharacterAnimRow(int32 InKey) const;

private:
	static UCMS* Singleton;

	UDataTable* CharacterAnimTable;

};
