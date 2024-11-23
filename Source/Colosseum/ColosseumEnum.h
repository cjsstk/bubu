// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define DEFAULT_WEAPON_TYPE 1

UENUM(BlueprintType)
enum class EInputActionType : uint8
{
	None,
	Move,
	Look,
	Dodge,
	Focus,
	BlockStarted,
	BlockFinished,
	Combo,
	Smash,
	Max,
};

UENUM(BlueprintType)
enum class EFSMActionType : uint8
{
	Idle,
	Block,
	Dodge,		// Character
	Combo,		// Character
	Smash,		// Character
	Attack1,	// Enemy
	Attack2,	// Enemy
	Attack3,	// Enemy
	Attack4,	// Enemy
	Attack5,	// Enemy
	WeakHit,
	StrongHit,
	Max,
};

UENUM(BlueprintType)
enum class EDodgeDirection : uint8
{
	Front,
	Back,
	Left,
	Right,
	Max,
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Weak,
	Strong,
	Max,
};