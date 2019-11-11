// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/SuperItem.h"
#include "SheildItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API ASheildItem : public ASuperItem
{
	GENERATED_BODY()
public:
	ASheildItem();
	void Use() override;
	void DurationEnd() override;
};
