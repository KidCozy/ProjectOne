// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "Engine/GameInstance.h"
#include "ProjectOneGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API UProjectOneGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShake> CShakePistol;

	UProjectOneGameInstance(const FObjectInitializer& ObjectInitializer);
	void Init();
	void HitShake(TSubclassOf<UCameraShake> CShake, float Scalar);
};
