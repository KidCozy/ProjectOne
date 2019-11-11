// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectOne.h"
#include "GameFramework/PlayerController.h"
#include "POUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTONE_API APOUIPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> UIWidgetClass;

	UPROPERTY()
	class UUserWidget* UIWidgetInstance;
};
