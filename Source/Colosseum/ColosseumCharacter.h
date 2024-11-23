// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "ColosseumEnum.h"
#include "ColosseumCharacter.generated.h"

class AEnemyCharacter;


UCLASS(config=Game)
class AColosseumCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AColosseumCharacter();

	bool IsComboTiming() const;

	UFUNCTION(BlueprintCallable)
	EFSMActionType GetCurrentFSMState() const;

	UFUNCTION(BlueprintCallable)
	bool IsFocusing() const { return bIsFocusing; }

	UFUNCTION(BlueprintCallable)
	float GetForwardInputValue() const { return ForwadInputValue; }

	UFUNCTION(BlueprintCallable)
	float GetRightInputValue() const { return RightInputValue; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

	virtual void OnDamaged(AActor* Attacker, EDamageType DamageType, bool bFromSweep, const FHitResult& SweepResult, const FActionParams& Params) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BP_SetFocusMode(bool bInIsFocusing);

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Focus(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void BlockStarted(const FInputActionValue& Value);
	void BlockFinished(const FInputActionValue& Value);
	void Combo(const FInputActionValue& Value);
	void Smash(const FInputActionValue& Value);

	bool SetFocusMode(bool bInIsFocusing);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCharacterActionComponent* ActionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TMap<EInputActionType, class UInputAction*> InputActions;
	
	UPROPERTY()
	TWeakObjectPtr<class AEnemyCharacter> FocusTarget = nullptr;

	UPROPERTY(EditAnywhere)
	FVector DefaultCameraHeight = FVector(0, 0, 70.f);

	UPROPERTY(EditAnywhere)
	FVector FocusCameraHeight = FVector(0, 0, 150.f);

	bool bIsFocusing = false;
	float ForwadInputValue = 0.f;
	float RightInputValue = 0.f;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	class UCharacterActionComponent* GetActionComponent() const { return ActionComponent; }
};

