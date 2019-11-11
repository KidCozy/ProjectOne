// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Item/SuperItem.h"
#include "SuckSangItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API ASuckSangItem : public ASuperItem
{
	GENERATED_BODY()
public:
	ASuckSangItem();
	void Use() override;
	void DurationEnd() override;
protected:
	TArray<UMaterialInterface*> OwnerMaterials;
	UMaterialInterface*SuckSangMaterial;
};
