// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Item/ThrowableItem.h"
#include "SmokeGrenade.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API ASmokeGrenade : public AThrowableItem
{
	GENERATED_BODY()
	virtual void InitAssets() override;
public:
	virtual void Use() override;

};
