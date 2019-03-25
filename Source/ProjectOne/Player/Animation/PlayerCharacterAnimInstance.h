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
		bool isAim;

	UPlayerCharacterAnimInstance();

};