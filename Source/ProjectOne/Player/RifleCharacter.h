// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ProjectOneCharacter.h"
#include "RifleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API ARifleCharacter : public AProjectOneCharacter
{
	GENERATED_BODY()
public:
	ARifleCharacter();
	void SetResources() override;
};
