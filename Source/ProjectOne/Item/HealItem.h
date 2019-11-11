// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Item/SuperItem.h"
#include "HealItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API AHealItem : public ASuperItem
{
	GENERATED_BODY()
public:
	AHealItem();

	float HealAmount;

	UFUNCTION(BlueprintCallable)
	void SetHealItem(E_Item item);

	void Use() override;
};
