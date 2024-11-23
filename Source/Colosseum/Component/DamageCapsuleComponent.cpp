// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DamageCapsuleComponent.h"

#include "ColosseumCharacter.h"
#include "EnemyCharacter.h"

UDamageCapsuleComponent::UDamageCapsuleComponent()
{
	bHiddenInGame = true;

}

void UDamageCapsuleComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddUniqueDynamic(this, &UDamageCapsuleComponent::OnCapsuleOverlapped);
}

void UDamageCapsuleComponent::InitDamage(EDamageType const& InDamageType)
{
	bAppliedDamage = false;
	DamageType = InDamageType;
}

void UDamageCapsuleComponent::OnCapsuleOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsActive())
	{
		return;
	}

	if (OtherActor == GetOwner())
	{
		return;
	}

	if (bAppliedDamage)
	{
		return;
	}

	ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(OtherActor);
	if (!HitCharacter)
	{
		return;
	}
	
	bAppliedDamage = true;
	double Dot = HitCharacter->GetActorForwardVector().Dot(GetOwner()->GetActorForwardVector());

	FActionParams Params;
	Params.bFrontDamage = Dot <= 0.f;

	HitCharacter->OnDamaged(GetOwner(), DamageType, bFromSweep, SweepResult, Params);

	//OnDamagedDelegate.ExecuteIfBound(GetOwner(), DamageType, bFromSweep, SweepResult);
}
