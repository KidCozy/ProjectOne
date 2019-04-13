// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "AIController.h"
#include "ProjectOneAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API AProjectOneAIController : public AAIController
{
	GENERATED_BODY()
	

public:

	AProjectOneAIController();

	virtual void Tick(float delta) override;
	virtual void BeginPlay() override;
	virtual void Possess(APawn * InPawn) override;

	FTimerHandle  Delay;


	void Update();
};
