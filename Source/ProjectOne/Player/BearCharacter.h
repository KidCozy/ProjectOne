// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ProjectOneCharacter.h"
#include "BearCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API ABearCharacter : public AProjectOneCharacter
{
	GENERATED_BODY()
public:
	ABearCharacter();
protected:
	void SetResources() override;
	void SetInitWeapone() override;
	void Shooting(float tick) override;
};
