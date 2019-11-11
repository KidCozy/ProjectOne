// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Player/ProjectOneCharacter.h"
#include "WolfCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API AWolfCharacter : public AProjectOneCharacter
{
	GENERATED_BODY()
public:
	AWolfCharacter();
	void SetResources() override;
};
