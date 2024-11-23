// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Component/ActionComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class COLOSSEUM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void OnDamaged(AActor* Attacker, EDamageType DamageType, bool bFromSweep, const FHitResult& SweepResult, const FActionParams& Params);

	class UDamageCapsuleComponent* GetDamageCapsuleComponent() const { return DamageCapsule; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDamageCapsuleComponent* DamageCapsule;

private:


};
