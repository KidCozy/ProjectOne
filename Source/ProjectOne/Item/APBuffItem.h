// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Item/SuperItem.h"
#include "APBuffItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API AAPBuffItem : public ASuperItem
{
	GENERATED_BODY()
public:
	AAPBuffItem();
	void Use() override;
};
