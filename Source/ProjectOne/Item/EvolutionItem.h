// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/SuperItem.h"
#include "EvolutionItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API AEvolutionItem : public ASuperItem
{
	GENERATED_BODY()
public:
	AEvolutionItem();
	void Use() override;
};
