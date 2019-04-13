// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Cover.h"
#include "Wall.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API AWall : public ACover
{
	GENERATED_BODY()

	AWall();
public:
	virtual void BeginPlay() override;
};
