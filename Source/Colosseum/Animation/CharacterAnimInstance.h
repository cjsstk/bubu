// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ColosseumEnum.h"
#include "CharacterAnimInstance.generated.h"


/**
 *
 */
UCLASS()
class COLOSSEUM_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void SetHitInfo(EDamageType const& InDamageType, EDodgeDirection const& InDirection, FActionParams const& InParams);
	void RemoveHitInfo();

protected:
	// Transition Event
	UFUNCTION()
	void AnimNotify_StrongHitStart();

	UFUNCTION()
	void AnimNotify_StrongHitEnd();
	//


protected:
	UPROPERTY()
	bool bIsHit = false;

	UPROPERTY()
	EDamageType DamageType = EDamageType::Weak;

	UPROPERTY()
	EDodgeDirection HitDirection = EDodgeDirection::Front;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FActionParams ActionParams;
};



/**
 * 
 */
UCLASS()
class COLOSSEUM_API UCharacterAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:



protected:
	// Transition Event
	UFUNCTION()
	void AnimNotify_BlockStart();

	UFUNCTION()
	void AnimNotify_BlockEnd();
	//

private:
	class UCharacterActionComponent* GetActionComponent();

};
