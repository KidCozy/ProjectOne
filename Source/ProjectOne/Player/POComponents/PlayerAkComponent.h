// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "AkComponent.h"
#include "PlayerAkComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API UPlayerAkComponent : public UAkComponent
{
public:
	GENERATED_BODY()
	UPlayerAkComponent();
	void PlayShotSound();
	void SetPlayer(class AProjectOneCharacter* player);

public:
	UPROPERTY()
	class UAkAudioEvent* Pistol;

protected:
	UPROPERTY()
	class AProjectOneCharacter* Player;

};
