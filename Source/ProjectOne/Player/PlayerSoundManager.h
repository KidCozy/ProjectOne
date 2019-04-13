// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerSoundManager.generated.h"

UCLASS()
class PROJECTONE_API APlayerSoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerSoundManager();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sound")
	void PlayShotSound();
};
