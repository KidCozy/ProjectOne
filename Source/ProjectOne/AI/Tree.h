// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "AI/Cover.h"
#include "Tree.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API ATree : public ACover
{
	GENERATED_BODY()

	ATree();

public:
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent * Pivot;
};
