// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ColosseumAnimNotify.h"
#include "Component/ActionComponent.h"

void UComboEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UCharacterActionComponent* ActionComp = MeshComp->GetOwner()->GetComponentByClass<UCharacterActionComponent>();
	if (!ActionComp)
	{
		return;
	}

	if (ActionComp->IsReadyNextCombo())
	{
		ActionComp->GoNextCombo(ComboNum);
	}
}
