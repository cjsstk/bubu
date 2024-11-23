// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "ColosseumEnum.h"
#include "DamageCapsuleComponent.generated.h"

DECLARE_DELEGATE_FourParams(FDamagedDelegate, class AActor*, EDamageType, bool, const FHitResult&);

/**
 * 
 */
UCLASS()
class COLOSSEUM_API UDamageCapsuleComponent : public UCapsuleComponent
{
	GENERATED_BODY()
	
public:
	UDamageCapsuleComponent();

	virtual void BeginPlay() override;

	void InitDamage(EDamageType const& InDamageType);

	bool IsDamageApplied() const { return bAppliedDamage; }
	EDamageType const& GetDamageType() const { return DamageType; }

	FDamagedDelegate OnDamagedDelegate;

private:
	UFUNCTION()
	void OnCapsuleOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bAppliedDamage = false;
	EDamageType DamageType = EDamageType::Max;

};
