// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ProjectOneCharacter.h"
#include "LauncherCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API ALauncherCharacter : public AProjectOneCharacter
{
	GENERATED_BODY()
public:
	ALauncherCharacter();
	void SetResources() override;
};
