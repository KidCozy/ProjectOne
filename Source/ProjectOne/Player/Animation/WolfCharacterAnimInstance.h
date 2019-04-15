// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Animation/PlayerCharacterAnimInstance.h"
#include "WolfCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API UWolfCharacterAnimInstance : public UPlayerCharacterAnimInstance
{
	GENERATED_BODY()
public:
	UWolfCharacterAnimInstance();
	void Evolution() override;
protected:
	void SetRollMontage() override;
};
