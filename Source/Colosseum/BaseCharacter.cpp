// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Animation\CharacterAnimInstance.h"
#include "Component/DamageCapsuleComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DamageCapsule = CreateDefaultSubobject<UDamageCapsuleComponent>(TEXT("DamageCapsuleComp"));
	DamageCapsule->SetupAttachment(RootComponent);
	DamageCapsule->InitCapsuleSize(20.f, 80.f);
	DamageCapsule->SetActive(false);

}

void ABaseCharacter::OnDamaged(AActor* Attacker, EDamageType DamageType, bool bFromSweep, const FHitResult& SweepResult, const FActionParams& Params)
{
	UBaseAnimInstance* BaseAnimInstance = CastChecked<UBaseAnimInstance>(GetMesh()->GetAnimInstance());

	BaseAnimInstance->SetHitInfo(DamageType, Params.bFrontDamage ? EDodgeDirection::Front : EDodgeDirection::Back, Params);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



