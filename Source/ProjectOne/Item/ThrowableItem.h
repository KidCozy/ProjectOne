// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Item/SuperItem.h"
#include "GameFramework/Actor.h"
#include "ThrowableItem.generated.h"

UCLASS()
class PROJECTONE_API AThrowableItem : public ASuperItem
{
	GENERATED_BODY()
	
protected:
	float EmitterBegin = 0.0f;
	float EmitterRadius = 10.0f;
	float EmitterDuration = 5.0f;

	float DamageScalar = 0.0f;
	float DamageDuration = 0.0f;

	float LaunchVelocity = 100.0f;

public:	
	AThrowableItem();

protected:
	virtual void Aim();
	virtual void Launch();
};