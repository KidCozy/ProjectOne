// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
		virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Forward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isRoll;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isShooting;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UAnimMontage* ShotMontage;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UAnimMontage* F_RollMontage;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UAnimMontage* B_RollMontage;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UAnimMontage* R_RollMontage;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UAnimMontage* L_RollMontage;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	UAnimMontage* SecondRollMontage;

	UPlayerCharacterAnimInstance();

	virtual void Evolution();

	void RollBackMontage();

private:

	UFUNCTION()
	void AnimNotify_RollEnd();

	UFUNCTION()
	void AnimNotify_JumpEnd();

	UFUNCTION()
	void AnimNotify_ReloadEnd();

	UFUNCTION()
	void AnimNotify_Shootable();

protected:
	virtual void SetMontage();
};
