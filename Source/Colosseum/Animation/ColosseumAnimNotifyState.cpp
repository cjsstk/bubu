// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ColosseumAnimNotifyState.h"

#include "ColosseumCharacter.h"
#include "Component/DamageCapsuleComponent.h"

static TAutoConsoleVariable<int32> CVarDrawDamageCapsule
(
	TEXT("co.DrawDamageCapsule"),
	1,
	TEXT("Draw Damage Capsule."),
	ECVF_Cheat
);


void UComboAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AColosseumCharacter* Character = Cast<AColosseumCharacter>(MeshComp->GetOwner());
	if (Character)
	{
		Character->GetActionComponent()->SetComboTiming(true);
	}
}

void UComboAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AColosseumCharacter* Character = Cast<AColosseumCharacter>(MeshComp->GetOwner());
	if (Character)
	{
		Character->GetActionComponent()->SetComboTiming(false);
	}
}

void UDamageAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (!Character)
	{
		return;
	}

	UDamageCapsuleComponent* DamageCapsule = Character->GetDamageCapsuleComponent();
	if (!DamageCapsule)
	{
		return;
	}

	FVector ForwardOffset = Character->GetActorForwardVector() * ForwardDistance;
	FVector SocketLoc = Character->GetMesh()->GetSocketLocation(SocketName);
	SocketLoc.Z = Character->GetActorLocation().Z;

	DamageCapsule->SetCapsuleRadius(CapsuleRadius);
	DamageCapsule->SetWorldLocation(SocketLoc + ForwardOffset);
	DamageCapsule->SetActive(true);
	DamageCapsule->InitDamage(DamageType);
}

void UDamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (!Character)
	{
		return;
	}

	UDamageCapsuleComponent* DamageCapsule = Character->GetDamageCapsuleComponent();
	if (!DamageCapsule)
	{
		return;
	}

	FVector ForwardOffset = Character->GetActorForwardVector() * ForwardDistance;
	FVector SocketLoc = Character->GetMesh()->GetSocketLocation(SocketName);
	SocketLoc.Z = Character->GetActorLocation().Z;

	DamageCapsule->SetWorldLocation(SocketLoc + ForwardOffset);

	if (CVarDrawDamageCapsule.GetValueOnGameThread() > 0)
	{
		DrawDebugCapsule(Character->GetWorld(), DamageCapsule->GetComponentLocation(), DamageCapsule->GetUnscaledCapsuleHalfHeight(), DamageCapsule->GetUnscaledCapsuleRadius(), DamageCapsule->GetComponentRotation().Quaternion(), FColor::Red, false, 1.0f);
	}
}

void UDamageAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (!Character)
	{
		return;
	}

	Character->GetDamageCapsuleComponent()->SetActive(false);
}
