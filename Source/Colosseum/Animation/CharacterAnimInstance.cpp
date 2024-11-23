// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CharacterAnimInstance.h"

#include "Component/ActionComponent.h"


void UBaseAnimInstance::SetHitInfo(EDamageType const& InDamageType, EDodgeDirection const& InDirection, FActionParams const& InParams)
{
	bIsHit = true;
	DamageType = InDamageType;
	HitDirection = InDirection;
	ActionParams = InParams;
}

void UBaseAnimInstance::RemoveHitInfo()
{
	bIsHit = false;
}

void UBaseAnimInstance::AnimNotify_StrongHitStart()
{
	UActionComponent* ActionComp = GetOwningActor()->GetComponentByClass<UActionComponent>();
	if (!ActionComp)
	{
		return;
	}

	ActionComp->SetActionBlock(true);
}

void UBaseAnimInstance::AnimNotify_StrongHitEnd()
{
	UActionComponent* ActionComp = GetOwningActor()->GetComponentByClass<UActionComponent>();
	if (!ActionComp)
	{
		return;
	}

	ActionComp->SetActionBlock(false);
}

//
void UCharacterAnimInstance::AnimNotify_BlockStart()
{
	//UE_LOG(LogTemp, Log, TEXT("Block Started"));

	UCharacterActionComponent* ActionComp = GetActionComponent();
	if (!ActionComp)
	{
		return;
	}

	ActionComp->SetPlayingBlockAnimation(true);
}

void UCharacterAnimInstance::AnimNotify_BlockEnd()
{
	//UE_LOG(LogTemp, Log, TEXT("Block Ended"));

	UCharacterActionComponent* ActionComp = GetActionComponent();
	if (!ActionComp)
	{
		return;
	}

	ActionComp->SetPlayingBlockAnimation(false);
}

UCharacterActionComponent* UCharacterAnimInstance::GetActionComponent()
{
	return GetOwningActor()->GetComponentByClass<UCharacterActionComponent>();
}

