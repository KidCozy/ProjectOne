// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Item/SuperItem.h"
#include "SpeedBuffItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API ASpeedBuffItem : public ASuperItem
{
	GENERATED_BODY()
public:
	ASpeedBuffItem();
	void Use() override;
	void DurationEnd() override;
};
