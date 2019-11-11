// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProjectOneGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API AProjectOneGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<class AProjectOneCharacter*> AlivePlayers;

	UPROPERTY(BlueprintReadWrite)
	FVector CurrentCirclePosition;

	UPROPERTY(BlueprintReadWrite)
	FVector TargetCirclePosition;

	UPROPERTY(BlueprintReadWrite)
	float CurrentCircleRadius = 50000.0f;

	UPROPERTY(BlueprintReadWrite)
	float TargetCircleRadius;
};
