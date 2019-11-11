// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "AkComponent.h"
#include "POPlayerAkComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API UPOPlayerAkComponent : public UAkComponent
{
	GENERATED_BODY()
public:
	UPOPlayerAkComponent();
	void PlayPistolShotSound();
	void PlayBulletCrashSound();
public:
	UAkAudioEvent * PistolSound;
	UAkAudioEvent * BulletCrashSound;
};
